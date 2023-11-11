//
// Created by cx9ps3 on 01.11.2023.
//

#pragma once
#include "../memory_pool/AllocatedObject.hpp"
#include <filesystem>

namespace hexen::engine::core::assets
{
	/**
 	* @class IAsset
 	* @brief A class representing an Asset in memory.
 	*
 	* IAsset is designed as an interface with pure virtual methods
 	* that must be implemented in any derived classes.
 	* It represents an Asset with functions to load and save it,
 	* and accessors to get its name and raw data.
 	*
 	* @note This class inherits from the memory::AllocatedObject class.
 	*/

	class IAsset : public memory::AllocatedObject
	{
	public:

		/**
    	* @brief Default Virtual Destructor.
    	*/

		virtual ~IAsset() = default;

		/**
    	* @brief Pure virtual method to get the name of the Asset.
    	* @return The name of the Asset as a std::string.
    	*/

		[[nodiscard]] virtual std::string getName() const = 0;

		/**
    	* @brief Pure virtual method to get the raw data of the Asset.
    	* @return The raw data of the asset file.
    	*/

		[[nodiscard]] virtual  core::vptr getRawData()  = 0;

		/**
    	* @brief Pure virtual method to load the Asset from a given file path.
    	* @param pathToAsset The file path to the Asset.
    	*/

		virtual void load(const std::filesystem::path &pathToAsset) = 0;

		/**
    	* @brief Pure virtual method to save the Asset to a given file path.
    	* @param pathToAsset The file path to the location where the Asset and its raw file should be saved.
    	* @param pathToRawFile The file path to the location where the raw file of the Asset should be saved.
    	*/

		virtual void save(const std::filesystem::path &pathToAsset, const std::filesystem::path &pathToRawFile) = 0;
	};;
}// namespace hexen::engine::core::asset
