//
// Created by cx9ps3 on 01.11.2023.
//

#include "AssetsStorage.hpp"

#include <utility>
phmap::parallel_flat_hash_map<std::string, std::shared_ptr<hexen::engine::core::assets::AssetsStorage>> hexen::engine::core::assets::AssetsStorage::assetsStoragesInstances;

void hexen::engine::core::assets::AssetsStorage::setAssetsRootDirectory(const std::filesystem::path &newPath)
{
	assetsRootDirectory = newPath;
}

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
	addAssetsStorage("default-storage", rootDirectory);
}