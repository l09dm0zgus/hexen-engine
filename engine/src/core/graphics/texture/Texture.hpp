//
// Created by cx9ps3 on 06.01.23.
//

#pragma once


#include "../../memory_pool/AllocatedObject.hpp"
#include <SDL3/SDL.h>
#include <SDL_image.h>
#include <string>
namespace hexen::engine::graphics::gl
{
	/**
 	* @class Texture
 	* @brief This class represents a texture in the Hexen Engine.
 	*
 	* A texture is an OpenGL object that contains one or more images that all have the same image format.
 	* A texture can be used in two ways. It can be sourced from a pixel shader, or it can be used as a render target.
 	*
 	* @namespace hexen::engine::graphics::gl
 	*
 	*/

	class Texture : public core::memory::AllocatedObject
	{
	public:
		/**
     	* @brief Construct a new Texture object. Responsible for texture creation and initialization.
     	*
     	* @param pathToImage The path to the image file.
     	* @param wrapMode The wrapping mode for the texture.
     	* @param filterMode The filter mode for the texture.
     	*/

		explicit Texture(const std::string &pathToImage, int wrapMode = 0x2901, int filterMode = 0x2600);

		/**
     	* @brief It is responsible for binding the texture to a particular texture unit.
     	*
     	* @param id
     	*/

		void bind(core::u32 id) const;

		/**
    	* @brief Get the Texture's id
    	*
    	* @return core::u32 The id of the texture.
    	*/

		[[nodiscard]] core::u32 getId() const noexcept;

		/**
     	* @brief Destroy the Texture object and free the memory occupied by the texture.
     	*/

		~Texture() override;

		/**
		* @brief Copy constructor.
		*
		* This is the copy constructor which allows texture to be copied.
		* This constructor uses the default copy constructor provided by the compiler.
		*
		* @param texture The texture to be copied.
		*/
		Texture(const Texture &texture) = default;

		/**
		* @brief Move constructor.
		*
		* This is the move constructor which allows for cheap transfer of resources
		* during object copying. This constructor uses the default move constructor
		* provided by the compiler.
		*
		* @param texture Temporary object to be moved from.
		*/

		Texture(Texture &&texture) = default;

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

		Texture &operator=(const Texture &texture) = default;

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

		Texture &operator=(Texture &&texture) = default;

	private:
		SDL_Surface *surface {nullptr};
		core::u32 textureId;

		/**
     	* @brief Set the Texture Parameters [WRAP | MIN_FILTER | MAX_FILTER]
     	*
     	* @param wrapMode Specifies the wrap parameters for the texture.
     	* @param filterMode Specifies the filter parameters for the texture.
     	*/

		void setTextureParameters(int wrapMode, int filterMode);
	};
}// namespace hexen::engine::graphics::gl
