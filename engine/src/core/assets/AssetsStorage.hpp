//
// Created by cx9ps3 on 01.11.2023.
//

#pragma once
#include "../Types.hpp"
#include "IAsset.hpp"
#include <parallel_hashmap/phmap.h>

namespace hexen::engine::core::assets
{
	/**
 * @class AssetsStorage
 * @brief A class to handle the storage of assets for the application.
 *
 * The class uses a Parallel Hash Map for efficient storage and retrieval of assets. It also maintains the root directory path of all assets.
 */
	class AssetsStorage
	{
	public:

		/**
         * @brief Sets the root directory for all assets.
         * @param newPath The `std::filesystem::path` to the new root directory.
         *
         * This should be used to update the root directory path at runtime, if necessary.
         */
		static void setAssetsRootDirectory(const std::filesystem::path &newPath);

		/**
         * @brief Loads the asset of the specified type.
         * @tparam T Type of asset. Must be a class derived from `IAsset`.
         * @param pathToAsset The `std::filesystem::path` to the asset file.
         * @return A shared pointer to the loaded asset. If the asset is already loaded, returns a pointer to the existing asset.
         *
         * This method will add the asset load operation to the current performance profile (signified by `HEXEN_ADD_TO_PROFILE()`),
         * assert that the type T is derived from `IAsset`, and then attempt to find the asset in the `loadedAssets` map.
         * If found, it returns as it is. If not, it loads the asset, adds it to the map, and returns the asset.
         */

		template<typename T, std::enable_if_t<std::is_base_of_v<IAsset, T>, bool> = true>
		std::shared_ptr<T> loadAsset(const std::filesystem::path &pathToAsset)
		{
			HEXEN_ADD_TO_PROFILE();
			static_assert(std::is_base_of_v<IAsset, T>, "T must be  inherit from interface IAsset!");
			auto iter = loadedAssets.find(pathToAsset);
			if (iter != loadedAssets.end())
			{
				return std::dynamic_pointer_cast<T>(iter->second);
			}
			else
			{
				auto newAsset = memory::make_shared<T>();
				newAsset->load(assetsRootDirectory / pathToAsset);
				loadedAssets[pathToAsset] = newAsset;
				return newAsset;
			}
		}

	private:

		/**
         * @brief A hash map to store currently loaded assets.
         *
         * The key is the asset file path and the value is a shared pointer to the asset.
         */

		static phmap::parallel_flat_hash_map<std::filesystem::path, std::shared_ptr<IAsset>> loadedAssets;

		/**
         * @brief The root directory path for all assets.
         *
         * This is required for loading new assets.
         */

		static std::filesystem::path assetsRootDirectory;
	};
}// namespace hexen::engine::core::assets