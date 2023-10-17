//
// Created by cx9ps3 on 08.10.2023.
//

#pragma once
#include <memory_pool/AllocatedObject.hpp>

namespace hexen::engine::graphics
{
	/**
 	* @brief Enum representing texture filters.
 	*/

	enum class TextureFilter
	{
		NEAREST = 0,   /**< Nearest filter.*/
		LINEAR,    /**< Linear filter. */
	};

	/**
 	* @brief Texture class.
 	*
 	* @details A virtual base class representing a texture in a graphical context.
 	*/

	class Texture : public core::memory::AllocatedObject
	{
	public:

		/**
     	* @brief Virtual destructor.
     	*/

		virtual ~Texture() = default;

		/**
     	* @brief Get the width of the texture.
     	*
     	* @details This is a pure virtual function that needs to be implemented in derived classes.
     	*
     	* @return The width of the texture.
     	*/

		[[nodiscard]] virtual core::u32 getWidth() const = 0;

		/**
     	* @brief Get the height of the texture.
     	*
     	* @details This is a pure virtual function that needs to be implemented in derived classes.
     	*
     	* @return The height of the texture.
     	*/

		[[nodiscard]] virtual core::u32 getHeight() const = 0;

		/**
     	* @brief Bind the texture.
     	*
     	* @details This is a pure virtual function that needs to be implemented in derived classes.
     	*
     	* @param slot The slot to which the texture is to be bound.
     	*/

		virtual void bind(core::u32 slot = 0) const = 0;

		[[nodiscard]] virtual core::u32 getId() const = 0;
	};

	/**
 	* @brief 2D Texture class.
 	*
 	* @details A class representing a 2D texture in a graphical context.
 	*/

	class Texture2D : public Texture
	{
	public:

		/**
     	* @brief Create a Texture2D object.
     	*
     	* @param path The path to the texture file.
     	* @param filter The filter to use on the texture.
     	*
     	* @return A shared pointer to the created Texture2D object.
     	*/

		static std::shared_ptr<Texture2D> create(const std::string& path,TextureFilter filter);
	};
}// namespace hexen::engine::graphics
