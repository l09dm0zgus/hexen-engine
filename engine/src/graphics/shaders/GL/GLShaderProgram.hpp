//
// Created by cx9ps3 on 03.01.23.
//
#pragma once

#include "../ShaderFile.hpp"
#include "../ShaderProgram.hpp"
#include <Types.hpp>

namespace hexen::engine::graphics::gl
{
	/**
    * @class GLShaderProgram
    * @brief Represents a shader program that consists of a vertex and fragment shader.
    * @extends ShaderProgram
    * This class handles the compilation and linking of shaders from their respective file paths.
    */

	class GLShaderProgram : public ShaderProgram
	{
	public:

		/**
		* @brief Constructs a GLShaderProgram object.
		*
 		* This constructor creates GLShaderProgram using the shader files provided in the vector argument.
 		* Each shader file is read, compiled, and then linked to the shader program.
 		*
 		* @param shadersFiles A reference to a std::vector containing string paths to the shader files.
 		*/

		explicit GLShaderProgram(const std::vector<std::string> &shadersFiles);

		/**
 		* @class GLShaderProgram
 		* @namespace hexen::engine::graphics::gl::shader
 		*
 		* @brief A GLShaderProgram object represents a OpenGL shader program.
 		*
 		* Destructor for the GLShaderProgram class.
 		* This destructor deletes the vertex and fragment shaders.
 		*/

		~GLShaderProgram() override;

		/**
 		* @brief Binds the shader program for use in the current rendering context.
 		*/

		void bind() const override;

		/**
 		* @brief Unbinds the shader program from the current rendering context.
 		*/

		void unbind() const override;

		/**
     	* @brief Function that sets a 2D vector uniform in the shader program.
     	* @param name - The name of the uniform.
     	* @param value - The value of the vector.
     	*/

		void setVector2f(const std::string& name, const glm::vec2 &value) const override;

		/**
     	* @brief Function that sets a 3D vector uniform in the shader program.
     	* @param name - The name of the uniform.
     	* @param value - The value of the vector.
     	*/

		void setVector3f(const std::string& name, const glm::vec3 &value) const override;

		/**
     	* @brief Function that sets a 4D vector uniform in the shader program.
     	* @param name - The name of the uniform.
     	* @param value - The value of the vector.
     	*/

		void setVector4f(const std::string& name, const glm::vec4 &value) const override;

		/**
     	* @brief Function that sets a 2x2 matrix uniform in the shader program.
     	* @param name - The name of the uniform.
     	* @param value - The value of the matrix.
     	*/

		 void setMatrix2(const std::string& name, const glm::mat2 &value) const override;

		/**
     	* @brief Function that sets a 3x3 matrix uniform in the shader program.
     	* @param name - The name of the uniform.
     	* @param value - The value of the matrix.
     	*/

		void setMatrix3(const std::string& name, const glm::mat3 &value) const override;

		/**
     	* @brief Function that sets a 4x4 matrix uniform in the shader program.
     	* @param name - The name of the uniform.
     	* @param value - The value of the matrix.
     	*/

		void setMatrix4(const std::string& name, const glm::mat4 &value) const override;

		/**
     	* @brief Function that sets an integer uniform in the shader program.
     	* @param name - The name of the uniform.
     	* @param value - The value of the integer.
     	*/

		void setInteger(const std::string& name, core::i32 value) const override;

		/**
     	* @brief Function that sets a float uniform in the shader program.
     	* @param name - The name of the uniform.
     	* @param value - The value of the float.
     	*/

		void setFloat(const std::string& name, float value) const override;

	private:

		core::u32 shaderProgram {0};

		/**
 		* @brief Compiles all shaders in the array of shader data.
 		*
 		* This function iterates over all shaders in the shadersData array and compiles them using the compileShader function.
 		*/

		void compileShaders();

		/**
 		* @brief Compiles a shader from a file.
 		*
 		* This function compiles the shader provided through the ShaderFile parameter.
 		* After the compilation, the shader's ID is stored in the array of shader IDs.
 		*
 		* @param shaderFile The shader file to compile.
 		*/

		void compileShader(const ShaderFile &shaderFile);

		/**
 		* @brief This method is used to link GLSL shaders into a program.
 		*
 		* The method creates a new program, attaches all shaders from shadersIds collection,
 		* links all them together into a program and then asks to show the linker log.
 		* It updates the shaderProgram member of the GLShaderProgram class.
 		*
 		* @note This should be called after all shaders have been added to the shadersIds collection.
 		*
 		* This function uses several OpenGL functions internally:
 		*  - glCreateProgram() : Creates an empty program object and returns a non-zero value by which it can be referenced.
 		*  - glAttachShader() : Attaches a shader object to a program object.
 		*  - glLinkProgram() : Links a program object.
 		*
 		* @see showLinkerLog()
 		*/

		void linkShaders();

		/**
        * Retrieves the compiler log for a specific shader program.
        *
        * @param shader The identifier of the shader program to retrieve the compiler log from.
        * @note This method is noexcept.
        */

		void showCompilerLog(core::u32 shader) const noexcept;

		/**
 		* @brief Display the linker log
 		*
 		* This function gets the link status of the shader program.
 		* In case of an error, an error log is retrieved and displayed in the console log.
 		*
 		* @note This function does not throw exceptions.
 		*/

		void showLinkerLog() const noexcept;

		void shaderPathsToShaderFiles(const std::vector<std::string> &paths);

		std::vector<ShaderFile> shadersData;

		std::vector<core::u32> shadersIds;


	};
}// namespace hexen::engine::graphics::gl::shader
