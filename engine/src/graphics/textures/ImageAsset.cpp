//
// Created by cx9ps3 on 09.11.2023.
//

#include "ImageAsset.hpp"
#include <SDL_image.h>
#include <fstream>

void hexen::engine::graphics::ImageAsset::save(const std::filesystem::path &pathToAsset, const std::filesystem::path &pathToRawFile)
{
	HEXEN_ADD_TO_PROFILE();
	auto pathWithExtension = addExtension(pathToAsset, assetFileExtension);
	auto surface = IMG_Load(pathToRawFile.string().c_str());

	if (surface == nullptr)
	{
		SDL_Log("Error : Failed to load %s image.", pathToRawFile.string().c_str());
	}

	auto *format = surface->format;

	constexpr core::u8 eightBitsPerPixel = 8;
	constexpr core::u8 sixteenBitsPerPixel = 16;
	constexpr core::u8 thirtyTwoBitsPerPixel = 32;

	switch (format->BitsPerPixel)
	{
		case eightBitsPerPixel:
			assetDataFile["image_asset"]["format"] = format->Amask ? ImageFormat::RGBA8 : ImageFormat::RGB8;
			break;
		case sixteenBitsPerPixel:
			assetDataFile["image_asset"]["format"] = format->Amask ? ImageFormat::RGBA16 : ImageFormat::RGB16;
			break;
		case thirtyTwoBitsPerPixel:
			assetDataFile["image_asset"]["format"] = format->Amask ? ImageFormat::RGBA32 : ImageFormat::RGB32;
			break;
		default:
			assetDataFile["image_asset"]["format"] = format->Amask ? ImageFormat::RGBA8 : ImageFormat::RGB8;
			break;
	}

	height = surface->h;
	width = surface->w;
	pitch = surface->pitch;

	const auto  size = pitch * height;
	imagePixels.resize(size);
	imagePixels.assign(static_cast<char*>(surface->pixels), static_cast<char*>(surface->pixels) + size);

	assetDataFile["image_asset"]["pitch"] = pitch;
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
	return static_cast<core::vptr>(imagePixels.data());;
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
	std::cout << pathToAsset << "\n";
	auto pathWithExtension = addExtension(pathToAsset, assetFileExtension);
	HEXEN_ASSERT(std::filesystem::exists(pathWithExtension), "ERROR: Asset: " + pathWithExtension.string() + " not found!");

	std::ifstream const inFile(pathWithExtension, std::ios::binary);
	std::stringstream ss;
	ss << inFile.rdbuf();

	assetDataFile = nlohmann::json::from_bson(ss);

	//WTF? Need to create additional buffer, because with imagePixels it doesn't want to compile.
	std::vector<core::u8> buffer = assetDataFile["image_asset"]["raw_data"];
	std::copy(buffer.begin(), buffer.end(),std::back_inserter(imagePixels));

	height = getHeight();
	width = getWidth();

	pitch = assetDataFile["image_asset"]["pitch"];
}

hexen::engine::graphics::ImageAsset::ImageFormat hexen::engine::graphics::ImageAsset::getFormat() const
{
	HEXEN_ADD_TO_PROFILE();
	return static_cast<ImageFormat>(assetDataFile["image_asset"]["format"]);
}

void hexen::engine::graphics::ImageAsset::flip()
{
	HEXEN_ADD_TO_PROFILE();
	auto *temp = new core::u8[pitch]; // intermediate buffer
	auto *pixels = imagePixels.data();

	for(int i = 0; i < height / 2; ++i)
	{
		// get pointers to the two rows to swap
		auto *row1 = pixels + i * pitch;
		auto *row2 = pixels + (height - i - 1) * pitch;

		// swap rows
		memcpy(temp, row1, pitch);
		memcpy(row1, row2, pitch);
		memcpy(row2, temp, pitch);
	}

	const auto size = pitch * height;

	imagePixels.resize(size);
	imagePixels.assign(pixels, pixels + size);

	delete[] temp;

}

std::string_view hexen::engine::graphics::ImageAsset::getExtension()
{
	return assetFileExtension;
}
