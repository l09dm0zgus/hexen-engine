//
// Created by cx9ps3 on 03.01.23.
//

#pragma once

#include "ShaderProgram.hpp"
#include <string>
namespace hexen::engine::graphics
{
	/**
 	* @class ShaderFile
 	* @brief This class represents a shader file in the HexenEngine project.
 	*
 	* The ShaderFile class encapsulates the information and functionality
 	* related to a shader file. This includes handling of shader file I/O and
 	* its properties. More detailed description of the class would go here,
 	* explaining its role in the larger project context.
 	*
 	* Example usage:
 	* ShaderFile shaderFile("path/to/shader");
 	*
 	* Some more information/explanation if necessary.
 	*/


	class ShaderFile
	{
	private:
		std::string shaderText;
		ShaderType type;

		void setShaderType(const std::string &path);

	public:

		/**
        * @brief Reads from a shader file and parses it.
        * @details This method reads from a shader file. If the file fails to open, an error
        * message is logged, if there is a failure during reading, an error message is logged.
        *
        * @param path The path of the shader file to be read.
        */

		void read(const std::string &path);

		/**
        * @brief Provides the content of the shader file as a string.
        * @details This method provides the content of the shader file as a string. If the file
        * has not been read before calling this method, it will likely return an empty string.
        *
        * @return A pointer to the shader text.
        */

		char *getContent();


	};

}// namespace hexen::engine::graphics::shader
