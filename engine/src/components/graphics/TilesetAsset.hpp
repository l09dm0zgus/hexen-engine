//
// Created by cx9ps3 on 30.01.2024.
//

#pragma once
#include <assets/IAsset.hpp>
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

namespace hexen::engine::components::graphics::assets
{

	/**
 	* @brief Represents a tileset asset, storing tileset properties and data.
 	*
 	* This class encapsulates information about a tileset, including tile dimensions,
 	* spacing, margins It inherits from the IAsset
 	* interface, allowing for integration with the engine's asset management system.
	* @extends IAsset
 	*/

	class TilesetAsset : public core::assets::IAsset
	{
	private:
		nlohmann::json tilesetData;
		std::filesystem::path pathToFile;
		glm::ivec2 tileSize {32};
		glm::ivec2 tilesCount {4};
		glm::ivec2 tilesetSize {tileSize * tilesCount};
		glm::vec2 spacing {0.0f};
		glm::vec2 imageMargin {0.9f};

		static constexpr std::string_view assetFileExtension = "hxts";

	public:
		/**
     	* @brief Returns the tileset's name.
     	*
     	* This function retrieves the name of the tileset as stored in the internal
     	* JSON data.
     	*
     	* @return The name of the tileset.
     	*/

		[[nodiscard]] std::string getName() const override;


		/**
     	* @brief Returns a pointer to the raw tileset data (JSON string).
     	*
     	* This function provides a pointer to the internal JSON object representing
     	* the tileset data. It can be used for serialization or communication with
     	* other systems.
     	*
     	* @return A pointer to the raw tileset data (JSON string).
     	*/

		[[nodiscard]] core::vptr getRawData() override;

		/**
     	* @brief Loads tileset data from a JSON file.
     	*
     	* This function parses a JSON file located at the specified path and extracts
     	* the tileset properties like tile size, number of tiles, spacing, margins,
     	* and stores them internally.
     	*
     	* @param pathToAsset The path to the JSON file containing tileset data.
     	*/

		void load(const std::filesystem::path &pathToAsset) override;

		/**
     	* @brief Saves tileset data to a JSON file.
     	*
     	* This function serializes the internal tileset data (dimensions, spacing,
     	* margins, etc.) into a JSON format and saves it to the specified file path.
     	*
     	* @param pathToAsset The path to save the tileset asset file.
     	* @param pathToRawFile The path to the raw tileset image file (unused in this implementation).
     	*/

		void save(const std::filesystem::path &pathToAsset, [[maybe_unused]] const std::filesystem::path &pathToRawFile) override;

		/**
 		* @brief Updates the path to the underlying tileset image file.
 		*
	 	* This function stores the provided path within the internal JSON data, associating it with
 		* the tileset asset. This path is crucial for loading and displaying the actual tileset
 		* image when needed.
 		*
 		* @param newPathToTilesetImage The new path to the tileset image file.
 		*/

		void setPathToTilesetImage(const std::filesystem::path &newPathToTilesetImage);

		/**
 		* @brief Retrieves the path to the tileset image file as stored in the tileset data.
 		*
 		* This function returns the previously set path to the tileset image file, allowing
 		* other parts of the engine to access and load the image for rendering or other purposes.
 		*
 		* @return The path to the tileset image file.
 		*/

		std::filesystem::path getPathToTilesetImage();

		/**
     	* @brief Sets the dimensions of individual tiles within the tileset.
     	*
     	* This function updates the internal tile size property with the provided
     	* new dimensions (width and height). It also updates the tileset size and
     	* potentially other calculations based on the new tile size.
     	*
     	* @param newTileSize The new tile size (width and height).
     	*/

		void setTileSize(const glm::ivec2 &newTileSize);

		/**
     	* @brief Returns the dimensions of individual tiles within the tileset.
     	*
     	* This function retrieves the current tile size (width and height) from
     	* the internal tileset data.
     	*
     	* @return The tile size (width and height).
     	*/

		glm::ivec2 getTileSize();

		/**
     	* @brief Calculates and returns the overall size of the tileset image based on the number of tiles and their individual dimensions.
     	*
     	* This function takes into account the number of tiles horizontally and vertically, along with the individual tile size, to determine the total width and height of the tileset image.
     	*
     	* @return The overall size of the tileset image (width and height).
     	*/

		glm::ivec2 getTilesetSize();


		/**
     	* @brief Sets the spacing between tiles within the tileset.
     	*
     	* This function updates the internal spacing property with the provided
     	* new spacing values (horizontal and vertical).
     	*
     	* @param newSpacing The new spacing between tiles (x and y).
     	*/

		void setSpacing(const glm::vec2 &newSpacing);

		/**
     	* @brief Returns the spacing between tiles within the tileset.
     	*
     	* This function retrieves the current spacing between tiles (horizontal
     	* and vertical) from the internal tileset data.
     	*
     	* @return The spacing between tiles (x and y).
     	*/

		glm::vec2 getSpacing();

		/**
     	* @brief Sets the margin around the image within the tileset.
     	*
     	* This function updates the internal image margin property with the provided new values, defining the extra space around the edges of the tileset image.
     	*
     	* @param newMargin The new margin around the image (horizontal and vertical).
     	*/

		void setImageMargin(const glm::vec2 &newMargin);

		/**
     	* @brief Retrieves the current margin around the image within the tileset.
     	*
     	* This function returns the current horizontal and vertical margin around the tileset image as stored in the internal tileset data.
     	*
     	* @return The current image margin (horizontal and vertical).
     	*/

		glm::vec2 getImageMargin();


		/**
     	* @brief Updates the number of tiles within the tileset.
     	*
     	* This function modifies the internal tile count property with the provided new values, specifying the horizontal and vertical count of tiles in the set. It also recalculates the overall tileset size based on the new tile count.
     	*
     	* @param newCount The new number of tiles (horizontal and vertical).
     	*/

		void setTilesCount(const glm::ivec2 &newCount);

		/**
     	* @brief Retrieves the current number of tiles within the tileset.
     	*
     	* This function returns the current horizontal and vertical count of tiles as stored in the internal tileset data.
     	*
     	* @return The current number of tiles (horizontal and vertical).
     	*/

		glm::ivec2 getTilesCount();

		/**
     	* @brief Saves the tileset data to the specified file path.
     	*
     	* This function calls the `save(const std::filesystem::path &pathToAsset, [[maybe_unused]] const std::filesystem::path &pathToRawFile)` method with the provided path to save the tileset asset file.
     	*
     	* @param pathToFile The path to save the tileset asset file.
     	*/

		void saveToFile();

		/**
 		* @brief Get the Image asset's file extension
 		*
 		* This function is part of the Hexen engine's graphics module.
 		* It provides an interface to access the extension of an image file asset.
 		*
 		* @return std::string_view represents the file extension of the image asset.
 		*/

		static std::string_view getExtension();
	};
}// namespace hexen::engine::components::graphics::assets
