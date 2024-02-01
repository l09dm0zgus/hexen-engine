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
		explicit AssetsStorage(std::filesystem::path &&rootDirectory);
		explicit AssetsStorage(const std::filesystem::path &rootDirectory);

		/**
 		* @brief Sets the root directory for assets and optionally moves existing assets to the new location
 		*
 		* This function changes the root directory of the assets. If moveContentToNewRoot is set to `true`,
 		* it also attempts to move the current asset files from the old directory to the new one.
 		* If an error occurs during the file transfer, it is caught and the exception message is printed to standard output.
 		* At the end of the operation, regardless of whether the files were moved or not, the provided newPath becomes the new assets root directory.
 		*
 		* @param newPath A std::filesystem::path object representing the new root directory for the assets
 		* @param moveContentToNewRoot A boolean value, if set to `true` it attempts to move the current assets to newPath
 		*
 		* @throws std::exception If an error occurs during file transfer
 		*/

		void setAssetsRootDirectory(const std::filesystem::path &newPath, bool moveContentToNewRoot = false);

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
			return nullptr;
		}

		/**
 		* @brief  A template function that creates an asset of type `T` which is inherited from `IAsset` interface.
 		* The function first checks if an asset with the same path already exists, if so, it saves the existing asset;
 		* if not, it creates a new asset, saves it, and stores it in the `loadedAssets` map.
 		*
 		* @tparam T                         The type of the asset to be created. Must be inherited from `IAsset` interface.
 		* @param  pathToAsset               The path where the asset will be saved.
 		* @param  pathToRawFile             The raw file path where the asset data is to be read from(optional).
 		*
 		* @pre     The type T must be inherited from `IAsset` interface.
 		*
 		* @return A shared pointer to the newly created or existing asset of type `T`.
 		*         In case of re-saving an existing asset, `nullptr` is returned.
 		*
 		* @exception Throws static_assert fail if the type `T` is not inherited from `IAsset` interface.Assertion if pathToRawFile does not exist.
 		*
 		*/

		template<typename T, std::enable_if_t<std::is_base_of_v<IAsset, T>, bool> = true>
		std::shared_ptr<T> createAsset(const std::filesystem::path &pathToAsset, const std::filesystem::path &pathToRawFile = "")
		{
			HEXEN_ADD_TO_PROFILE();
			static_assert(std::is_base_of_v<IAsset, T>, "T must be  inherit from interface IAsset!");
			HEXEN_ASSERT(std::filesystem::exists(pathToRawFile),"File with path: " + pathToRawFile.string() + " does not exist!");

			auto iter = loadedAssets.find(pathToAsset);
			if (iter != loadedAssets.end())
			{
				auto asset = std::dynamic_pointer_cast<T>(iter->second);
				asset->load(assetsRootDirectory / pathToAsset);
			}
			else
			{
				auto newAsset = memory::make_shared<T>();
				newAsset->save(assetsRootDirectory / pathToAsset, pathToRawFile);
				loadedAssets[pathToAsset] = newAsset;
				return newAsset;
			}
			return nullptr;
		}

		/**
 		* @brief Fetches the assets storage instance associated with the given name.
 		*
 		* This function tries to find an existing assets storage instance related to the given name. If the given
 		* assets storage name does not exist, the function asserts and prints an error message.
 		*
 		* @param storageName Name of the assets storage you want to get.
 		* @return std::shared_ptr to the assets storage instance. If the storage does not exist the program should terminate.
 		*
 		* @throws HEXEN_ASSERT error if storageName is not found among assetsStoragesInstances.
 		*/

		static std::shared_ptr<AssetsStorage> getAssetsStorageByName(const std::string &storageName);

		/**
 		* @brief This function adds a new assets storage to the storage instances.
 		*
 		* @param storageName The name of the new storage to be added.
 		* @param rootDirectory The root directory of the new storage assets.
 		*
 		* The function constructs a new AssetsStorage object from the received root directory
 		* and adds it to the assetsStoragesInstances map with the provided name as a key.
 		*/

		static void addAssetsStorage(const std::string &storageName, const std::filesystem::path &rootDirectory);

		/**
 		* @brief Gets the default asset storage.
 		*
 		* This function returns a shared pointer to the default AssetsStorage instance.
 		* The default asset storage is determined by using the defaultStorageName.
 		*
 		* @return A std::shared_ptr to the default AssetsStorage object.
 		*/

		static std::shared_ptr<AssetsStorage> getDefaultAssetsStorage();

		/**
 		* @brief This method is used to add a default assets storage having specified root directory.
 		*
		* @param rootDirectory The filesystem path of the directory to register as the "default-storage".
		*
 		* This functions wraps and simplifies the usage of addAssetsStorage
 		* by providing "default-storage" as the storage name, and the root,
 		* as the location of assets.
 		*
 		*/

		static void addDefaultStorage(const std::filesystem::path &rootDirectory);

		bool isAssetFileExist(const std::filesystem::path &pathToAsset) const;
	private:
		/**
         * @brief A hash map to store currently loaded assets.
         *
         * The key is the asset file path and the value is a shared pointer to the asset.
         */

		phmap::parallel_flat_hash_map<std::filesystem::path, std::shared_ptr<IAsset>> loadedAssets;

		/**
         * @brief The root directory path for all assets.
         *
         * This is required for loading new assets.
         */

		std::filesystem::path assetsRootDirectory;

		/**
 		* @brief Checks if the asset file exists in the asset storage.
 		*
 		* This function checks if a particular asset file exists in the assetsRootDirectory.
 		* It appends the provided path to the root directory and checks the existence of the file.
 		*
 		* @param pathToAsset Relative file path to the asset in the assetsRootDirectory.
 		* @return bool Returns true if the asset file exists, false otherwise.
 		*/

		static phmap::parallel_flat_hash_map<std::string, std::shared_ptr<AssetsStorage>> assetsStoragesInstances;

		static const std::string defaultStorageName;
	};

	/**
 	* @class AssetHelper
 	* @brief A helper class for loading and creating assets
 	*
 	* This class contains two utility static member functions for loading and creating assets.
 	* The loading and creation operations are conducted via the specified asset storage, defaulting to "default-storage".
 	*/

	class AssetHelper
	{
	public:

		/**
		* @warning If not storageName not set, asset loaded from default storage.
     	* @brief  Loads an asset of the specified type from a given path.
     	* @tparam T The type of asset to load. Must be a type that is derived from IAsset
     	* @param  pathToAsset The filesystem path to the asset to load
     	* @param  storageName The name of the asset storage to use for loading, defaults to "default-storage"
     	* @return A shared_ptr to the loaded asset of  type T
     	*/

		template<typename T, std::enable_if_t<std::is_base_of_v<IAsset, T>, bool> = true>
		static std::shared_ptr<T> loadAsset(const std::filesystem::path &pathToAsset, const std::string& storageName = "default-storage")
		{
			return AssetsStorage::getAssetsStorageByName(storageName)->loadAsset<T>(pathToAsset);
		}

		/**
 		* @brief Creates an asset of the specified type from a given path to raw file.
 		* @warning If the storageName is not set, the asset will be created in default storage.
 		* @tparam T The type of asset to create. The type must be derived from IAsset.
 		* @param pathToAsset The filesystem path to the asset to be created.
 		* @param pathToRawFile (Optional) The filesystem path to the raw file from which the asset will be created.
 		* @param storageName (Optional) The name of the asset storage to use for creation. Defaults to "default-storage".
 		* @param isRewriteAssetIfExist (Optional) If true, will overwrite the asset if it already exists. Defaults to false.
 		* @return A shared_ptr to the created asset of type T.
 		* @details This function will first check if the asset already exists in the specified storage.
 		*          If the asset exists and isRewriteAssetIfExist is false, the existing asset will be loaded and returned.
 		*          If the asset doesn't exist or isRewriteAssetIfExist is true, a new asset will be created from the raw file.
 		*/

		template<typename T, std::enable_if_t<std::is_base_of_v<IAsset, T>, bool> = true>
		static std::shared_ptr<T> createAsset(const std::filesystem::path &pathToAsset, const std::filesystem::path &pathToRawFile = "", const std::string& storageName = "default-storage", bool isRewriteAssetIfExist = false)
		{
			auto pathAssetWithExtension = pathToAsset;
			pathAssetWithExtension.replace_extension(T::getExtension());
			if(AssetsStorage::getAssetsStorageByName(storageName)->isAssetFileExist(pathAssetWithExtension) && !isRewriteAssetIfExist)
			{
				return loadAsset<T>(pathToAsset, storageName);
			}

			return AssetsStorage::getAssetsStorageByName(storageName)->createAsset<T>(pathToAsset, pathToRawFile);
		}
	};;
}// namespace hexen::engine::core::assets