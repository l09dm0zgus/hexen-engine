//
// Created by cx9ps3 on 03.01.23.
//

#pragma once
#include <string>
#include <assets/AssetsStorage.hpp>
#include <nlohmann/json.hpp>
#include "ShaderProgram.hpp"

namespace hexen::engine::graphics
{
	/**
 	* @class ShaderAsset
 	* @brief This class represents a shader file in the HexenEngine project.
 	*
 	* The ShaderAsset class encapsulates the information and functionality
 	* related to a shader file. This includes handling of shader file I/O and
 	* its properties. More detailed description of the class would go here,
 	* explaining its role in the larger project context.
 	*
 	*
 	* @extends IAsset
 	*/


	class ShaderAsset : public core::assets::IAsset
	{
	private:
		std::string shaderText;
		hexen::engine::graphics::ShaderType type;

		/**
 		* @brief Parse the shader type from a shader file.
 		*
 		* This function looks for a `#type` token in the given shader file, follows
 		* the token until the end of line and returns the type as a string.
 		*
 		* @return std::string Shader type as read from the file. It could be any of the types specified in the shader file.
 		* @throws HEXEN_ASSERT exception if #type token is not found in the shader file.
 		*/

		std::string parseShaderType();

		/**
 		* @brief Set shader type based on a provided string.
 		*
 		* The function sets the shader type to `VERTEX` if the provided string is "vertex",
 		* `FRAGMENT` if the string is "fragment" or "pixel", `GEOMETRY` if the string is "geometry",
 		* and to `UNKNOWN` otherwise.
 		*
 		* @param shaderType String representing the shader type.
 		* @throws HEXEN_ASSERT exception if unsupported shader type is specified.
 		*/

		void setShaderType(const std::string &shaderType);

		nlohmann::json assetDataFile;

	public:

		/**
     	* @brief Gets the name of the shader asset.
     	* @return String representing the name of the shader asset.
     	*/

		[[nodiscard]] std::string getName() const override;

		/**
     	* @brief Gets the raw shader data.
     	* @return std::vector storing bytes of the raw shader data.
     	*/

		[[nodiscard]] core::vptr getRawData()  override;

		/**
     	* @brief Load shader asset from the given path.
     	* @param pathToAsset Path to the shader asset file.
     	* @sideeffect May modify 'assetDataFile', and other member variables.
     	*/

		void load(const std::filesystem::path &pathToAsset) override;


		/**
     	* @brief Saves shader data in the asset file.
     	* @param pathToAsset The path to save the asset file.
     	* @param pathToRawShader The path to the raw shader file.
     	* @sideeffect May modify 'shaderText', assetDataFile, and other member variables.
     	*/

		void save(const std::filesystem::path &pathToAsset,const std::filesystem::path &pathToRawShader) override;

		/**
 		* @brief Get the currently set shader type.
 		*
 		* The function is `noexcept`, so it does not throw exceptions.
 		*
 		* @retun hexen::engine::graphics::ShaderType The shader type currently set in this ShaderAsset.
 		*/

		[[nodiscard]] hexen::engine::graphics::ShaderType getType() const noexcept;

		/**
 		* @brief Retrieves shader text.
 		*
 		* This method in the class hexen::engine::graphics::ShaderAsset, returns
 		* the shader text as a raw pointer.
 		* @note This function is declared as noexcept, meaning that it doesn't throw exceptions.
 		*
 		* @return Const char pointer to the stored shader text.
 		*/

		[[nodiscard]] const char* getShaderText() const noexcept;
	};

}// namespace hexen::engine::graphics::shader
