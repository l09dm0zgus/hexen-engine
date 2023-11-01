//
// Created by cx9ps3 on 01.11.2023.
//

#include "AssetsStorage.hpp"
std::filesystem::path hexen::engine::core::assets::AssetsStorage::assetsRootDirectory;
phmap::parallel_flat_hash_map<std::filesystem::path, std::shared_ptr<hexen::engine::core::assets::IAsset>> hexen::engine::core::assets::AssetsStorage::loadedAssets;

void hexen::engine::core::assets::AssetsStorage::setAssetsRootDirectory(const std::filesystem::path &newPath)
{
	assetsRootDirectory = newPath;
}
