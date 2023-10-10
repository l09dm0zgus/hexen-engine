//
// Created by cx9ps3 on 09.10.2023.
//

#pragma once
#include <memory_pool/AllocatedObject.hpp>
#include <glm/glm.hpp>

namespace hexen::engine::graphics
{
	enum class ShaderType : core::u8
	{
		UNKNOWN = 0,
		VERTEX,
		GEOMETRY,
		FRAGMENT
	};

	class ShaderProgram
	{
	public:
		virtual ~ShaderProgram()  = default;

		virtual void bind() const = 0;
		virtual void unbind()  const = 0;

		virtual void setVector2f(const std::string& name, const glm::vec2 &value) = 0;
		virtual void setVector3f(const std::string& name, const glm::vec3 &value) = 0;
		virtual void setVector4f(const std::string& name, const glm::vec4 &value) = 0;

		virtual void setMatrix2(const std::string& name, const glm::vec2 &value) = 0;
		virtual void setMatrix3(const std::string& name, const glm::vec3 &value) = 0;
		virtual void setMatrix4(const std::string& name, const glm::vec4 &value) = 0;

		virtual void setInteger(const std::string& name, core::i32 value) = 0;
		virtual void setFloat(const std::string& name, float value) = 0;

		static std::shared_ptr<ShaderProgram> create(std::vector<std::string> &pathsToShaders);
	};
}

