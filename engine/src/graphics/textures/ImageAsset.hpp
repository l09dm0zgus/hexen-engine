//
// Created by cx9ps3 on 09.11.2023.
//

#pragma once
#include <SDL_surface.h>
#include <assets/IAsset.hpp>
#include <nlohmann/json.hpp>

namespace hexen::engine::graphics
{
	/**
 	* @class ImageAsset
 	* @brief Handles image assets, inheriting from IAsset interface
 	* @extends IAsset
 	* @details This class provides handling for image files of various formats. It provides methods
 	*  to load, save, retrieve raw data and other properties of image assets.
 	*/

	class ImageAsset : public core::assets::IAsset
	{
	private:
		/** @brief JSON file for storing asset data */
		nlohmann::json assetDataFile;


		core::i32 height {0};
		core::i32 width {0};
		core::i32 channels {0};
		std::vector<core::u8> imagePixels;
		static constexpr std::string_view assetFileExtension = "hximage";
		bool bIsFlipped = false;

	public:
		/**
    	* @enum ImageFormat
    	* @brief Supported image formats
    	*/

		enum class ImageFormat : core::u8
		{
			RED = 1,
			RGB = 3,
			RGBA = 4
		};

		~ImageAsset() override = default;

		/**
    	* @brief Get the format of the image.
    	* @return Enum representing the format of the image.
    	*/

		[[nodiscard]] ImageFormat getFormat() const;

		/**
    	* @brief Get the name of the Asset.
    	* @return The name of the Asset as a std::string.
    	*/

		[[nodiscard]] std::string getName() const override;

		/**
    	* @brief Get the raw data of the Asset.
    	* @return The pixels from image.
    	*/

		[[nodiscard]] core::vptr getRawData() override;

		/**
         * @brief Loads an image asset from the specified filesystem path.
         *
         * This function reads the specified file as binary, loads its contents into a stringstream,
         * then converts the stringstream content from BSON to JSON format.
         * The raw image data is then retrieved from the JSON object and assigned to rawImageData.
         * In case of any errors during the process, appropriate exceptions are thrown.
         *
         * @param pathToAsset The filesystem path of the image asset to be loaded.
         */

		void load(const std::filesystem::path &pathToAsset) override;

		/**
 		* @brief Saves an image as an asset.
 		*
 		* This function reads an image file from the specified pathToRawFile, determines its height, width,
 		* and format, and writes this data along with the image's raw pixel data to an asset file at the specified pathToAsset.
 		*
 		* @param[in] pathToAsset  The filesystem path where the asset file will be saved.
 		* @param[in] pathToRawFile The filesystem path where the raw image file is stored.
 		*
 		* @warning If the loading of the image file fails, the function will log an error message using SDL_Log.
 		*          It uses JSON for BSON to serialize the asset data and write it to the asset file.
 		*
 		* @note The function automatically detects the format of the image based on its pixel depth.
 		*       Supported formats are RGB8, RGBA8, RGB16, RGBA16, RGB32, and RGBA32.
 		*       If the format does not correspond to any of the supported formats, it will default to RGB8.
 		*/

		void save(const std::filesystem::path &pathToAsset, const std::filesystem::path &pathToRawFile) override;

		/**
    	* @brief Get the height of the image.
    	* @return The height of the image.
    	*/

		core::i32 getHeight() const;

		/**
    	* @brief Get the width of the image.
    	* @return The width of the image.
    	*/

		core::i32 getWidth() const;

		/**
 		* @brief Flips the image asset vertically.
 		*
 		* This function flips the image on a central horizontal axis through the use of a temporary
 		* buffer. It operates in-place on the pixel data of the image asset.
 		*
 		*/

		void flip();

		/**
 		* @brief Get the Image asset's file extension
 		*
 		* This function is part of the Hexen engine's graphics module.
 		* It provides an interface to access the extension of an image file asset.
 		*
 		* @return std::string_view represents the file extension of the image asset.
 		*/

		static std::string_view getExtension();

		/**
		 * @brief Checks if called flip()
		 * @see ImageAsset::flip()
		 * @return bIsFlipped
		 */

		[[nodiscard]] bool isFlipped();
	};
}// namespace hexen::engine::graphics
