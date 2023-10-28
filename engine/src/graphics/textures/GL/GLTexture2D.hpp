//
// Created by cx9ps3 on 06.01.23.
//

#pragma once


#include "SDL3/SDL.h"
#include "SDL_image.h"
#include "../Texture.hpp"
#include <string>


namespace hexen::engine::graphics::gl
{
	int textureFilterToGLTextureFilter(TextureFilter textureFilter);


	/**
 	* @class GLTexture2D
 	* @brief This class represents a texture in the Hexen Engine.
 	*
 	* A texture is an OpenGL object that contains one or more images that all have the same image format.
 	* A texture can be used in two ways. It can be sourced from a pixel shader, or it can be used as a render target.
 	*
 	* @namespace hexen::engine::graphics::gl
 	*
 	*/

	class GLTexture2D : public Texture2D
	{
	public:
		/**
     	* @brief Construct a new GLTexture2D object. Responsible for texture creation and initialization.
     	*
     	* @param pathToImage The path to the image file.
     	* @param filter The filter mode for the texture.
     	*/

		explicit GLTexture2D(const std::string &pathToImage,TextureFilter filter);

		/**
 		* @brief Binds a texture to a specified texture unit.
 		*
 		* This function binds a texture to a texture unit. The texture unit number is given by the parameter.
 		* The texture itself is an OpenGL object whose ID is stored in this class's `textureId` member.
 		*
 		* @note This function is a const function and will not modify the state of the object.
 		*
 		* @param slot The texture unit to which the texture is to be bound (represented as a core::u32 integer).
 		*/

		void bind(core::u32 slot = 0) const override;

		/**
    	* @brief Get the GLTexture2D's id
    	*
    	* @return core::u32 The id of the texture.
    	*/

		[[nodiscard]] core::u32 getId() const override;

		/**
     	* @brief Destroy the GLTexture2D object and free the memory occupied by the texture.
     	*/

		~GLTexture2D() override;

		/**
		* @brief Copy constructor.
		*
		* This is the copy constructor which allows texture to be copied.
		* This constructor uses the default copy constructor provided by the compiler.
		*
		* @param texture The texture to be copied.
		*/
		GLTexture2D(const GLTexture2D &texture) = default;

		/**
		* @brief Move constructor.
		*
		* This is the move constructor which allows for cheap transfer of resources
		* during object copying. This constructor uses the default move constructor
		* provided by the compiler.
		*
		* @param texture Temporary object to be moved from.
		*/

		GLTexture2D(GLTexture2D &&texture) = default;

		/**
		* @brief Copy assignment operator.
		*
		* This is the copy assignment operator, which allows for assigning of values
		* from one texture object to another. This operator uses default copy assignment
		* operator provided by the compiler.
		*
		* @param texture The source texture for the assignment.
		* @return Reference to this, after the assignment.
		*/

		GLTexture2D &operator=(const GLTexture2D &texture) = default;

		/**
		* @brief Move assignment operator.
		*
		* This operator is used for move semantics, typically when an object is
		* a temporary. This operator uses default move assignment operator
		* provided by the compiler.
		*
		* @param texture Temporary object to be moved from.
		* @return Reference to this, after the assignment.
		*/

		GLTexture2D &operator=(GLTexture2D &&texture) = default;


		[[nodiscard]] core::u32 getWidth() const override { return  width; };
		[[nodiscard]] core::u32 getHeight() const override { return height; };

	private:
		core::u32 textureId;
		core::u32 height;
		core::u32 width;

	};
}// namespace hexen::engine::graphics::gl
