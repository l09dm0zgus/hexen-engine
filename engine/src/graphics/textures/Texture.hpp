//
// Created by cx9ps3 on 08.10.2023.
//

#pragma once
#include <glm/vec2.hpp>
#include <memory_pool/AllocatedObject.hpp>

namespace hexen::engine::graphics
{
	class ImageAsset;
	/**
 	* @brief Enum representing texture filters.
 	*/

	enum class TextureFilter
	{
		NEAREST = 0, /**< Nearest filter.*/
		LINEAR,		 /**< Linear filter. */
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
     	* @param imageAsset The asset of image asset file.
     	* @param filter The filter to use on the texture.
     	* @param flipImage Default parameter - false,set true for flip image
     	* @return A shared pointer to the created Texture2D object.
     	*/

		static std::shared_ptr<Texture2D> create(const std::shared_ptr<ImageAsset> &imageAsset, TextureFilter filter, bool flipImage = false);
	};

	/**
 	*  @class TextureArray
 	*
 	*  @brief A class for handling 2D texture arrays.
 	*
 	*  This class is derived from the abstract Texture class and
 	*  provides the interface for creating and managing a 2D texture array.
 	*
 	*  @sa Texture
 	*
 	*/

	class TextureArray : public Texture
	{
	public:
		/**
         * @brief Default virtual destructor.
         */

		virtual ~TextureArray() = default;

		/**
         * @brief Abstract method to add a new texture to the texture array.
         *
         * @param[in] imageAsset The path to the image asset file to add to the texture array.
         * @param[in] flipImage Default parameter - false,set true for flip image.
         */

		virtual void addTextureToArray(const std::shared_ptr<ImageAsset> &path, bool flipImage = false) = 0;

		/**
         * @brief Static factory method to create a new TextureArray instance.
         *
         * @param[in] size The size (width and height) of the textures in the array.
         * @param[in] filter The filter to use when sampling the textures.
         *
         * @return Shared pointer to the newly created TextureArray instance.
         */

		static std::shared_ptr<TextureArray> create(const glm::vec2 &size, TextureFilter filter);

		/**
 		* @brief A function of the TextureArray class inside the hexen::engine::graphics namespace.
 		*
 		* This function is used to increment the count of texture units.
 		*/

		static core::u32 getCountOfTextureUnits();
	protected:

		/**
 		* @brief A function of the TextureArray class inside the hexen::engine::graphics namespace.
 		*
 		* This function is used to increment the count of texture units.
 		*/

		static void increaseCountOfTextureUnits();
	private:
		static core::u32 countOfTextureUnits;
	};
}// namespace hexen::engine::graphics
