//
// Created by cx9ps3 on 30.01.2024.
//

#include "TilesetAsset.hpp"
#include <fstream>

void hexen::engine::components::graphics::assets::TilesetAsset::save(const std::filesystem::path &pathToAsset, [[maybe_unused]] const std::filesystem::path &pathToRawFile)
{
	tilesetData["tileset_asset"]["name"] = pathToAsset.filename().string();

	tilesetData["tileset_asset"]["path_to_image_asset"] = "";

	tilesetData["tileset_asset"]["tiles_count"]["rows"] = tilesCount.x;
	tilesetData["tileset_asset"]["tiles_count"]["columns"] = tilesCount.y;

	tilesetData["tileset_asset"]["tile_size"]["width"] = tileSize.x;
	tilesetData["tileset_asset"]["tile_size"]["height"] = tileSize.y;

	tilesetData["tileset_asset"]["tileset_size"]["width"] = tilesetSize.x;
	tilesetData["tileset_asset"]["tileset_size"]["height"] = tilesetSize.y;

	tilesetData["tileset_asset"]["spacing"]["x"] = spacing.x;
	tilesetData["tileset_asset"]["spacing"]["y"] = spacing.y;

	tilesetData["tileset_asset"]["margin"]["x"] = imageMargin.x;
	tilesetData["tileset_asset"]["margin"]["y"] = imageMargin.y;

	pathToFile = addExtension(pathToAsset,assetFileExtension);

	saveToFile();
}

void hexen::engine::components::graphics::assets::TilesetAsset::load(const std::filesystem::path &pathToAsset)
{
	std::ifstream file(addExtension(pathToAsset,assetFileExtension));
	tilesetData = nlohmann::json::parse(file);
}

std::string hexen::engine::components::graphics::assets::TilesetAsset::getName() const
{
	return tilesetData["tileset_asset"]["name"];
}

hexen::engine::core::vptr hexen::engine::components::graphics::assets::TilesetAsset::getRawData()
{
	return (core::vptr)tilesetData.dump().c_str();
}

void hexen::engine::components::graphics::assets::TilesetAsset::setTileSize(const glm::ivec2 &newTileSize)
{
	tileSize = newTileSize;
	tilesetData["tileset_asset"]["tile_size"]["width"] = tileSize.x;
	tilesetData["tileset_asset"]["tile_size"]["height"] = tileSize.y;
}

glm::ivec2 hexen::engine::components::graphics::assets::TilesetAsset::getTileSize()
{
	return {tilesetData["tileset_asset"]["tile_size"]["width"], tilesetData["tileset_asset"]["tile_size"]["width"]};
}

glm::ivec2 hexen::engine::components::graphics::assets::TilesetAsset::getTilesetSize()
{
	return {tilesetData["tileset_asset"]["tileset_size"]["width"], 	tilesetData["tileset_asset"]["tileset_size"]["height"] = tilesetSize.y};
}

void hexen::engine::components::graphics::assets::TilesetAsset::setSpacing(const glm::vec2 &newSpacing)
{
	spacing = newSpacing;
	tilesetData["tileset_asset"]["spacing"]["x"] = spacing.x;
	tilesetData["tileset_asset"]["spacing"]["y"] = spacing.y;
}

glm::vec2 hexen::engine::components::graphics::assets::TilesetAsset::getSpacing()
{
	return {tilesetData["tileset_asset"]["spacing"]["x"], tilesetData["tileset_asset"]["spacing"]["y"]};
}

void hexen::engine::components::graphics::assets::TilesetAsset::setImageMargin(const glm::vec2 &newMargin)
{
	imageMargin = newMargin;
	tilesetData["tileset_asset"]["margin"]["x"] = imageMargin.x;
	tilesetData["tileset_asset"]["margin"]["y"] = imageMargin.y;
}

glm::vec2 hexen::engine::components::graphics::assets::TilesetAsset::getImageMargin()
{
	return {tilesetData["tileset_asset"]["margin"]["x"], tilesetData["tileset_asset"]["margin"]["y"]};
}

void hexen::engine::components::graphics::assets::TilesetAsset::setTilesCount(const glm::ivec2 &newCount)
{
	tilesCount = newCount;

	tilesetData["tileset_asset"]["tiles_count"]["rows"] = tilesCount.x;
	tilesetData["tileset_asset"]["tiles_count"]["columns"] = tilesCount.y;
}

glm::ivec2 hexen::engine::components::graphics::assets::TilesetAsset::getTilesCount()
{
	return {tilesetData["tileset_asset"]["tiles_count"]["rows"], tilesetData["tileset_asset"]["tiles_count"]["columns"]};
}

void hexen::engine::components::graphics::assets::TilesetAsset::saveToFile()
{
	std::ofstream file(pathToFile);
	file << tilesetData.dump();
}

std::string_view hexen::engine::components::graphics::assets::TilesetAsset::getExtension()
{
	return assetFileExtension;
}

void hexen::engine::components::graphics::assets::TilesetAsset::setPathToTilesetImage(const std::filesystem::path &newPathToTilesetImage)
{
	tilesetData["tileset_asset"]["path_to_image_asset"] = newPathToTilesetImage.string();
}

std::filesystem::path hexen::engine::components::graphics::assets::TilesetAsset::getPathToTilesetImage()
{
	return std::filesystem::path(tilesetData["tileset_asset"]["path_to_image_asset"]);
}
