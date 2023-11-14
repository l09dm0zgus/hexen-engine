//
// Created by cx9ps3 on 01.11.2023.
//

#include "AssetsStorage.hpp"

#include <utility>
phmap::parallel_flat_hash_map<std::string, std::shared_ptr<hexen::engine::core::assets::AssetsStorage>> hexen::engine::core::assets::AssetsStorage::assetsStoragesInstances;
const std::string hexen::engine::core::assets::AssetsStorage::defaultStorageName = "default-storage";

std::shared_ptr<hexen::engine::core::assets::AssetsStorage> hexen::engine::core::assets::AssetsStorage::getAssetsStorageByName(const std::string &storageName)
{
	auto it = assetsStoragesInstances.find(storageName);
	HEXEN_ASSERT(it != assetsStoragesInstances.end(), "ERROR:Assets storage with name: " + storageName + " does not exist!")
	return it->second;
}

hexen::engine::core::assets::AssetsStorage::AssetsStorage(std::filesystem::path &&rootDirectory) : assetsRootDirectory(std::move(rootDirectory))
{
}

hexen::engine::core::assets::AssetsStorage::AssetsStorage(const std::filesystem::path &rootDirectory) : assetsRootDirectory(rootDirectory)
{
}

void hexen::engine::core::assets::AssetsStorage::addAssetsStorage(const std::string &storageName, const std::filesystem::path &rootDirectory)
{
	assetsStoragesInstances[storageName] = memory::make_shared<AssetsStorage>(rootDirectory);
}

void hexen::engine::core::assets::AssetsStorage::addDefaultStorage(const std::filesystem::path &rootDirectory)
{
	addAssetsStorage(defaultStorageName, rootDirectory);
}

bool hexen::engine::core::assets::AssetsStorage::isAssetFileExist(const std::filesystem::path &pathToAsset) const
{
	return std::filesystem::exists(assetsRootDirectory / pathToAsset);
}

void hexen::engine::core::assets::AssetsStorage::setAssetsRootDirectory(const std::filesystem::path &newPath, bool moveContentToNewRoot)
{
	if(moveContentToNewRoot)
	{
		try
		{
			std::filesystem::copy(assetsRootDirectory, newPath, std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);
		}
		catch (std::exception& e)
		{
			std::cout << e.what();
		}
	}
	assetsRootDirectory = newPath;
}

std::shared_ptr<hexen::engine::core::assets::AssetsStorage> hexen::engine::core::assets::AssetsStorage::getDefaultAssetsStorage()
{
	return getAssetsStorageByName(defaultStorageName);
}
