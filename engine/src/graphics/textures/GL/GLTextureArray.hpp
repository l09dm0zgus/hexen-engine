//
// Created by cx9ps3 on 28.10.2023.
//

#pragma once
#include "../Texture.hpp"

namespace hexen::engine::graphics::gl
{
	/**
 	* @class GLTextureArray
 	* @brief Class to handle OpenGL Texture Arrays.
 	* @details This class mainly handles texture array creation, binding and ID retrieval.
 	* @extends TextureArray
	*/

	class GLTextureArray : public TextureArray
	{
	private:
		/**
         * @brief The size of each image in the texture array.
         */
		glm::vec2 imageSize;

		/**
         * @brief The unique identifier for the texture.
         */
		core::u32 textureID;

		/**
         * @brief The index of the texture slot where the texture is bound.
         */
		core::u32 textureSlotIndex;

		/**
         * @brief The index of the last image added to the texture array.
         */
		core::u32 imageIndex;

	public:
		/**
         * @brief Constructor to create the texture array.
         * @param textureFilter The texture filter settings.
         * @param size The size of each image in the texture array.
         */
		explicit GLTextureArray(TextureFilter textureFilter, const glm::vec2 &size);

		/**
         * @brief Function to add a texture to the texture array.
         * @param path The path to the image file to be added to the texture array.
         */
		void addTextureToArray(const std::string &path) override;

		/**
         * @brief Get the width of the texture.
         * @return The width of the texture.
         */
		[[nodiscard]] core::u32 getWidth() const override;

		/**
         * @brief Get the height of the texture.
         * @return The height of the texture.
         */
		[[nodiscard]] core::u32 getHeight() const override;

		/**
         * @brief Bind the texture to the given slot.
         * @param slot The slot to which the texture is to be bound (default: 0).
         */
		void bind(core::u32 slot = 0) const override;

		/**
         * @brief Get the unique identifier for the texture.
         * @return The unique identifier for the texture.
         */
		[[nodiscard]] core::u32 getId() const override;
	};
}// namespace hexen::engine::graphics::gl