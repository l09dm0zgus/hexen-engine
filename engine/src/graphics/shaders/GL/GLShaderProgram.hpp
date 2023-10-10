//
// Created by cx9ps3 on 03.01.23.
//
#pragma once

#include "../ShaderFile.hpp"
#include "../ShaderProgram.hpp"
#include <core/Types.hpp>

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
		GLShaderProgram(std::vector<std::string> &shadersFiles);

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
        * @brief Activates the shader program for rendering.
        *
        * This function activates the shader program for rendering. It should be called before rendering any objects
        * that use this shader program.
        *
        * @note This function should be called within a rendering loop, typically before drawing each object.
        * @note Once a shader program is activated, all subsequent rendering commands will use this program until it is deactivated.
        * @note This function is noexcept, meaning it will not throw any exceptions.
        */

		void use() const noexcept;

		/**
        * Sets the value of an integer uniform variable in the shader program.
        *
        * @param uniformVariable The name of the uniform variable in the shader program.
        * @param value The integer value to set for the uniform variable.
        *
        * @note This method assumes that a valid shader program is already linked.
        *       Make sure to verify that the shader program has been linked before
        *       using this method.
        * @note This function is const and can be called on a const GLShaderProgram object.
        * @note This function assumes that the specified uniform variable exists in the shader program.
        *
        */


		void setIntUniform(const std::string &uniformVariable, core::i32 value) const;

		/**
        * @brief Set a mat4 uniform variable in the shader program.
        *
        * This function sets the value of a mat4 uniform variable in the shader program.
        *
        * @param uniformVariable The name of the uniform variable to set.
        * @param matrix The mat4 value to set for the uniform variable.
        *
        *
        * @note This method assumes that a valid shader program is already linked.
        *       Make sure to verify that the shader program has been linked before
        *       using this method.
        * @note This function is const and can be called on a const GLShaderProgram object.
        * @note This function assumes that the specified uniform variable exists in the shader program.
        *
        */


		void setMatrix4Uniform(const std::string &uniformVariable, const glm::mat4 &matrix) const;

		/**
    	* Sets a vector4 uniform variable in the shader program.
    	*
    	* @param uniformVariable The name of the uniform variable.
    	* @param vector The vector value to set.
    	*
    	* @note This method assumes that a valid shader program is already linked.
    	*       Make sure to verify that the shader program has been linked before
    	*       using this method.
    	* @note This function is const and can be called on a const GLShaderProgram object.
    	* @note This function assumes that the specified uniform variable exists in the shader program.
    	*
    	*
    	*/

		void setVector4Uniform(const std::string &uniformVariable, const glm::vec4 &vector) const;

		/**
    	* @brief Sets the value of a uniform variable of type vec3 in the shader program.
    	*
    	* This function sets the value of the uniform variable with the given name
    	* to the specified 3D vector. The uniform variable must exist in the shader program.
    	*
    	* @param uniformVariable The name of the uniform variable.
    	* @param vector The 3D vector value to set.
    	*
    	* @note The shader program must be currently active and linked in order to set the uniform variable.
    	*/

		void setVector3Uniform(const std::string &uniformVariable, const glm::vec3 &vector) const;

	private:
		/**
 		* @brief A ShaderFile object to manage the vertex shader file.
 		*/

		hexen::engine::graphics::ShaderFile vertexShaderFile;

		/**
 		* @brief A ShaderFile object to manage the fragment shader file.
 		*/

		hexen::engine::graphics::ShaderFile fragmentShaderFile;

		/**
 		* @brief Unsigned 32 bit integer to hold the vertex shader reference.
 		*/

		core::u32 vertexShader {0};

		/**
 		* @brief Unsigned 32 bit integer to hold the fragment shader reference.
  		*/

		core::u32 fragmentShader {0};

		/**
 		* @brief Unsigned 32 bit integer to hold the shader program reference.
 		*/

		core::u32 shaderProgram {0};

		/**
 		* @brief Pointer to a character array containing the loaded fragment shader text.
 		*/

		char *fragmentShaderText {nullptr};

		/**
 		* @brief Pointer to a character array containing the loaded vertex shader text.
 		*/

		char *vertexShaderText {nullptr};

		/**
        * @brief Compiles the vertex shader of the GLShaderProgram.
        *
        * This function compiles the vertex shader of the GLShaderProgram.
        * It retrieves the vertex shader source code from the shader program,
        * compiles it, and verifies if the compilation was successful.
        * If successful, the compiled vertex shader is attached to the shader program.
        * If unsuccessful, an error message is printed to the console.
        *
        * @note This function assumes that the GLShaderProgram has been properly initialized
        *       and that a valid vertex shader source code has been set.
        *       It does not handle resource management, such as shader cleanup.
        *
        */

		void compileVertexShader();

		/**
        * @brief Compiles the fragment shader of the GLShaderProgram.
        *
        * This function compiles the fragment shader source code associated with the GLShaderProgram object.
        * It retrieves the fragment shader source code from the shader program and compiles it using the
        * appropriate APIs provided by the rendering system. If the compilation succeeds, the compiled
        * fragment shader is attached to the GLShaderProgram object.
        *
        */

		void compileFragmentShader();

		/**
        * @brief Links multiple shaders into a shader program.
        *
        * This function is a member function of the GLShaderProgram class inside the core::rend::shader namespace.
        * It is responsible for linking multiple shaders together into a single shader program.
        *
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

		std::unordered_map<ShaderType,ShaderFile> shadersData;


	};
}// namespace hexen::engine::graphics::gl::shader
