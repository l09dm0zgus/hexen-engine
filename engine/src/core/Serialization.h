#pragma once

#include <iostream>
#include <vector>
#include "Types.h"
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>

#define _MAKE_FIELD_NAME(n) n##ReflextionData
#define MAKE_FIELD_NAME(n) _MAKE_FIELD_NAME(n)

namespace core
{
    template<typename T>
    struct ReflectionData
    {
        const char *variableName;
        T value;
        const char *rttiTypeName;
    };

    const auto  _pathToCache = std::filesystem::current_path().string() + std::string("/classes_caches/");
    struct ReflectionDataFromClass
    {
        std::string variableName;
        std::string value;
        std::string rttiTypeName;
    };
    nlohmann::json cacheFile;

    template<typename T>
    HEXEN_INLINE nlohmann::json& operator<<(nlohmann::json& j, T &&value)
    {
        j["value"] = std::forward<T>(value);
        return j;
    }
    template<typename T>
    HEXEN_INLINE nlohmann::json& operator>>(nlohmann::json& j, T &&value)
    {
        value = j["value"];
        return j;
    }

    HEXEN_INLINE nlohmann::json& operator<<(nlohmann::json& j,const glm::vec3 &vector)
    {
        j["x"] = vector.x;
        j["y"] = vector.y;
        j["z"] = vector.z;
        return j;
    };

    HEXEN_INLINE nlohmann::json& operator<<(nlohmann::json& j,const Color &color)
    {
        j["r"] = color.r;
        j["g"] = color.g;
        j["b"] = color.b;
        j["a"] = color.a;
        return j;
    }

    template<typename T>
    HEXEN_INLINE nlohmann::json& operator<<(nlohmann::json& j,const std::vector<T> &vector)
    {
        j["size"] = vector.size();
        for (int i = 0; i < vector.size(); i++)
        {
            j["elements"][i] << vector[i];
        }
        return j;
    }

    HEXEN_INLINE nlohmann::json& operator>>( nlohmann::json& j,glm::vec3 &vector)
    {
        vector.x = j["x"] ;
        vector.y = j["y"];
        vector.z = j["z"];
        return j;
    };

    HEXEN_INLINE nlohmann::json& operator>>(nlohmann::json& j,Color &color)
    {
        color.r = j["r"];
        color.g = j["g"];
        color.b = j["b"];
        color.a = j["a"];
        return j;
    };
    template<typename T>
    HEXEN_INLINE nlohmann::json& operator>>(nlohmann::json& j,std::vector<T> &vector)
    {

        vector.reserve(j["size"]);
        for (int i = 0; i < vector.size(); i++)
        {
            j["elements"][i] >> vector[i];
        }
        return j;
    };

    template<typename T>
    HEXEN_INLINE nlohmann::json storeToJson(const ReflectionData<T>& reflectionData)
    {
        auto nameHash = std::to_string(hashString(reflectionData.variableName));
        nlohmann::json j;

        j[nameHash]["name"] = reflectionData.variableName;
        j[nameHash] << reflectionData.value;
        j[nameHash]["rtti"]  = reflectionData.rttiTypeName;

        return j;
    }

    template<typename T>
    HEXEN_INLINE std::string getClassCacheFileName(const char *className)
    {
        return std::string(className) + "-" + std::to_string(typeid(T).hash_code())+".cache";
    }

    template<typename T,class U>
    HEXEN_INLINE ReflectionData<T> restoreReflectionData(nlohmann::json &j, const std::string &nameHash)
    {
        ReflectionData<T> reflectionData;

        reflectionData.variableName =  j[nameHash]["name"].get<std::string>().c_str();
        j[nameHash] >> reflectionData.value;
        reflectionData.rttiTypeName = j[nameHash]["rtti"].get<std::string>().c_str();

        return reflectionData;

    }

    template<typename T,class U>
    HEXEN_INLINE ReflectionData<T> storeReflectionData(const char *variableName, const char *className, const T &typeData)
    {
        std::ofstream file(_pathToCache + getClassCacheFileName<U>(className));
        ReflectionData<T> reflectionData{variableName,typeData, typeid(T).name()};
        cacheFile["cache"].push_back(storeToJson(reflectionData));
        file << cacheFile;
        return reflectionData;
    }

    template<typename T> HEXEN_INLINE std::vector<ReflectionDataFromClass> getAllSerializedClassVariables(const char *className)
    {
        std::vector<ReflectionDataFromClass> variables;
        std::ifstream file(_pathToCache + getClassCacheFileName<T>(className));
        auto cacheFile = nlohmann::json::parse(file)["cache"];

        for(auto &i : cacheFile)
        {
            for(auto &j : i)
            {
                ReflectionDataFromClass reflectionDataFromClass;
                reflectionDataFromClass.variableName = j["name"];
                reflectionDataFromClass.value =  nlohmann::to_string(j["value"]);
                reflectionDataFromClass.rttiTypeName = j["rtti"];
                variables.push_back(reflectionDataFromClass);
            }
        }
        return variables;
    }

    template<typename T,class U>
    HEXEN_INLINE ReflectionData<T> serialize(const char *variableName, const char *className, const T &typeData)
    {
        if(!std::filesystem::exists(_pathToCache))
        {
            std::filesystem::create_directory(_pathToCache);
        }
        if(std::filesystem::exists(_pathToCache + getClassCacheFileName<U>(className)))
        {
            std::ifstream file(_pathToCache + getClassCacheFileName<U>(className));

            std::fstream listCache(_pathToCache + "cached_classes_list.cache", std::ios::app | std::ios::in | std::ios::out);

            std::string line;
            bool isCachedClassExist{false};

            while(std::getline(listCache, line ))
            {
                if(line == getClassCacheFileName<U>(className))
                {
                    isCachedClassExist = true;
                    break;
                }
            }

            listCache << getClassCacheFileName<U>(className) << "\n";

            auto cacheFile = nlohmann::json::parse(file)["cache"];

            auto nameHash = std::to_string(hashString(variableName));

            for(auto &element:cacheFile)
            {
                auto it = element.find(nameHash);
                if(it != element.end())
                {
                    return restoreReflectionData<T, U>(element, nameHash);
                }
            }
            return storeReflectionData<T, U>(variableName, className, typeData);
        }
        else
        {
            return storeReflectionData<T, U>(variableName, className, typeData);
        }
    }

}


#define REFLECTION_DATA_FIELD(varName,className) \
\
realone::core::ReflectionData<decltype(varName)>   MAKE_FIELD_NAME(varName) = core::serialize<decltype(varName),className>(#varName,#className,varName); \


#define SERIALIZABLE_FIELD(className,varName)  REFLECTION_DATA_FIELD(varName,className)

#define GET_ALL_SERIALIZED_VARIABLES(className)   core::getAllSerializedClassVariables<className>(#className)

#define  LOAD_FIELD(varName) varName = MAKE_FIELD_NAME(varName).value;