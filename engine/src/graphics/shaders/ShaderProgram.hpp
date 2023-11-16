//
// Created by cx9ps3 on 09.10.2023.
//

#pragma once
#include <glm/glm.hpp>
#include <memory_pool/AllocatedObject.hpp>

namespace hexen::engine::graphics
{
	class ShaderAsset;
	enum class ShaderType : core::u8
	{
		UNKNOWN = 0,
		VERTEX,
		GEOMETRY,
		FRAGMENT
	};

	/**
	* @class ShaderProgram
 	* @brief This class is an abstract representation for a shader program.
 	*/

	class ShaderProgram
	{
	public:

		/**
     	* @brief Virtual default destructor.
     	*/

		virtual ~ShaderProgram() = default;

		/**
     	* @brief Pure virtual function for binding the shader program.
     	*/

		virtual void bind() const = 0;

		/**
     	* @brief Pure virtual function for unbinding the shader program.
     	*/

		virtual void unbind() const = 0;

		/**
     	* @brief Function that sets a 2D vector uniform in the shader program.
     	* @param name - The name of the uniform.
     	* @param value - The value of the vector.
     	*/

		virtual void setVector2f(const std::string& name, const glm::vec2 &value) const = 0;

		/**
     	* @brief Function that sets a 3D vector uniform in the shader program.
     	* @param name - The name of the uniform.
     	* @param value - The value of the vector.
     	*/

		virtual void setVector3f(const std::string& name, const glm::vec3 &value) const = 0;

		/**
     	* @brief Function that sets a 4D vector uniform in the shader program.
     	* @param name - The name of the uniform.
     	* @param value - The value of the vector.
     	*/

		virtual void setVector4f(const std::string& name, const glm::vec4 &value) const = 0;

		/**
     	* @brief Function that sets a 2x2 matrix uniform in the shader program.
     	* @param name - The name of the uniform.
     	* @param value - The value of the matrix.
     	*/

		virtual void setMatrix2(const std::string& name, const glm::mat2 &value) const = 0;

		/**
     	* @brief Function that sets a 3x3 matrix uniform in the shader program.
     	* @param name - The name of the uniform.
     	* @param value - The value of the matrix.
     	*/

		virtual void setMatrix3(const std::string& name, const glm::mat3 &value) const = 0;

		/**
     	* @brief Function that sets a 4x4 matrix uniform in the shader program.
     	* @param name - The name of the uniform.
     	* @param value - The value of the matrix.
     	*/

		virtual void setMatrix4(const std::string& name, const glm::mat4 &value) const = 0;

		/**
     	* @brief Function that sets an integer uniform in the shader program.
     	* @param name - The name of the uniform.
     	* @param value - The value of the integer.
     	*/

		virtual void setInteger(const std::string& name, core::i32 value) const = 0;

		/**
     	* @brief Function that sets a float uniform in the shader program.
     	* @param name - The name of the uniform.
     	* @param value - The value of the float.
     	*/

		virtual void setFloat(const std::string& name, float value) const = 0;

		/**
     	* @brief Function that sets a integer array uniform in the shader program.
     	* @param name - The name of the uniform.
     	* @param values - The array.
     	* @param count - count of the array elements.
     	*/

		virtual void setIntegerArray(const std::string& name, core::i32* values, core::u32 count) const = 0;

		/**
     	* @brief Factory method for creating a ShaderProgram instance.
     	* @param shaderAssets - A vector of shaders assets files.
     	* @return A shared pointer to a ShaderProgram instance.
     	*/

		static std::shared_ptr<ShaderProgram> create(const std::vector<std::shared_ptr<ShaderAsset>> &shaderAssets);
	};
}

