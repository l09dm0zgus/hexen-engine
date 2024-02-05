//
// Created by cx9ps3 on 09.11.2023.
//

#include "ImageAsset.hpp"
#include <fstream>
#include <sstream>


#define STB_IMAGE_IMPLEMENTATION
#include "STBImage.h"

void hexen::engine::graphics::ImageAsset::save(const std::filesystem::path &pathToAsset, const std::filesystem::path &pathToRawFile)
{
	HEXEN_ADD_TO_PROFILE();
	auto pathWithExtension = addExtension(pathToAsset, assetFileExtension);
	auto pixels = stbi_load(pathToRawFile.string().c_str(), &width, &height, &channels, STBI_rgb_alpha);
	imagePixels.clear();
	std::copy(pixels, pixels + (width * STBI_rgb_alpha) * height, std::back_inserter(imagePixels));

	assetDataFile["image_asset"]["format"] = static_cast<ImageFormat>(channels);
	assetDataFile["image_asset"]["size"]["width"] = width;
	assetDataFile["image_asset"]["size"]["height"] = height;
	assetDataFile["image_asset"]["name"] = pathToRawFile.filename();
	assetDataFile["image_asset"]["raw_data"] = imagePixels;

	auto binaryJsonData = nlohmann::json::to_bson(assetDataFile);
	std::ofstream outFile(pathWithExtension, std::ios::binary);

	outFile.write((char *) binaryJsonData.data(), binaryJsonData.size() * sizeof(core::u8));
}

hexen::engine::core::vptr hexen::engine::graphics::ImageAsset::getRawData()
{
	HEXEN_ADD_TO_PROFILE();
	return static_cast<core::vptr>(imagePixels.data());
	;
}

hexen::engine::core::i32 hexen::engine::graphics::ImageAsset::getHeight() const
{
	HEXEN_ADD_TO_PROFILE();
	return assetDataFile["image_asset"]["size"]["height"];
}

hexen::engine::core::i32 hexen::engine::graphics::ImageAsset::getWidth() const
{
	HEXEN_ADD_TO_PROFILE();
	return assetDataFile["image_asset"]["size"]["width"];
}
std::string hexen::engine::graphics::ImageAsset::getName() const
{
	HEXEN_ADD_TO_PROFILE();
	return assetDataFile["image_asset"]["name"];
}

void hexen::engine::graphics::ImageAsset::load(const std::filesystem::path &pathToAsset)
{
	HEXEN_ADD_TO_PROFILE();
	auto pathWithExtension = addExtension(pathToAsset, assetFileExtension);
	HEXEN_ASSERT(std::filesystem::exists(pathWithExtension), "ERROR: Asset: " + pathWithExtension.string() + " not found!");

	std::ifstream const inFile(pathWithExtension, std::ios::binary);
	std::stringstream ss;
	ss << inFile.rdbuf();

	assetDataFile = nlohmann::json::from_bson(ss);

	imagePixels.clear();
	//WTF? Need to create additional buffer, because with imagePixels it doesn't want to compile.
	std::vector<core::u8> buffer = assetDataFile["image_asset"]["raw_data"];
	std::copy(buffer.begin(), buffer.end(), std::back_inserter(imagePixels));

	height = getHeight();
	width = getWidth();
}

hexen::engine::graphics::ImageAsset::ImageFormat hexen::engine::graphics::ImageAsset::getFormat() const
{
	HEXEN_ADD_TO_PROFILE();
	return static_cast<ImageFormat>(assetDataFile["image_asset"]["format"]);
}

void hexen::engine::graphics::ImageAsset::flip()
{
	HEXEN_ADD_TO_PROFILE();
	bIsFlipped = true;
	core::u32 pitch = STBI_rgb_alpha * width;
	auto *temp = new core::u8[pitch];// intermediate buffer
	auto *pixels = imagePixels.data();

	for (int i = 0; i < height / 2; ++i)
	{
		// get pointers to the two rows to swap
		auto *row1 = pixels + i * pitch;
		auto *row2 = pixels + (height - i - 1) * pitch;

		// swap rows
		memcpy(temp, row1, pitch);
		memcpy(row1, row2, pitch);
		memcpy(row2, temp, pitch);
	}

	imagePixels.resize(pitch * height);
	imagePixels.assign(pixels, pixels + pitch);

	delete[] temp;
}

std::string_view hexen::engine::graphics::ImageAsset::getExtension()
{
	return assetFileExtension;
}

bool hexen::engine::graphics::ImageAsset::isFlipped()
{
	return bIsFlipped;
}
