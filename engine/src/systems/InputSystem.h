//
// Created by cx9ps3 on 02.09.2023.
//

#pragma once
#include "../core/memory_pool/AllocatedObject.h"
#include <nlohmann/json.hpp>
#include <functional>
#include "../gui/IGUI.h"
#include "../core/input_devices/Mouse.h"

namespace core
{
    class Window;
}

namespace sys::input
{
    class InputSystem : public core::mem::AllocatedObject
    {

    private:
        std::unique_ptr<core::input::Mouse> mouse;

        nlohmann::json keyMappingsFile;
        core::HashTable<std::string,std::function<void()>> actionMappingCallbacks;
        core::HashTable<std::string,std::function<void(float)>> axisMappingsCallbacks;
        std::string path;
        std::vector<std::shared_ptr<gui::IGUI>> guis;
    public:
        struct ActionMapping
        {
            ActionMapping(const std::string& name,core::u32 sdlKey) : name(name), sdlKey(sdlKey) {};
            core::u32 sdlKey;
            std::string name;
        };

        struct AxisMapping
        {
            AxisMapping(const std::string& name,float value,core::u32 sdlKey) : name(name),value(value),sdlKey(sdlKey) {};
            core::u32 sdlKey;
            float value;
            std::string name;
        };

        void addNewAxisMapping(const std::string& name,float value,core::u32 sdlKey);
        void addNewAxisMapping(const AxisMapping& axisMapping);

        void addNewActionMapping(const std::string& name,core::u32 sdlKey);
        void addNewActionMapping(const ActionMapping& actionMapping);

        void bindAction(const std::string& name,const std::function<void()> &actionCallback);
        void bindAxis(const std::string& name,const std::function<void(float)> &axisCallback);

        void changeMapping(const std::string& name,core::u32, core::u32 newKey);

        explicit InputSystem(const std::string &pathToFile = "mappings.json");
        ~InputSystem() override = default;
        void processInput(const std::shared_ptr<core::Window> &window);
        void addGUI(const std::shared_ptr<gui::IGUI> &gui);
    private:

        void createMappingsFile();
        void loadMappingsFile();
        std::vector<ActionMapping> actionMappings;
        std::vector<AxisMapping> axisMappings;
    };

}
