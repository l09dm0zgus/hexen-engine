//
// Created by cx9ps3 on 04.01.23.
//

#pragma once

#include "../Component.hpp"
#include <textures/Texture.hpp>
#include <vector>

namespace hexen::engine::graphics
{
	class ImageAsset;
}
namespace hexen::engine::components::graphics
{
	class SpriteComponent : public Component
	{
	public:

		SpriteComponent() = default;

		explicit SpriteComponent(const std::shared_ptr<engine::graphics::ImageAsset> &imageAsset);

		~SpriteComponent() override = default;

		void setTexture(const std::shared_ptr<engine::graphics::ImageAsset> &imageAsset);

		std::shared_ptr<engine::graphics::ImageAsset> getTexture();

	private:
		std::shared_ptr<engine::graphics::ImageAsset> mainTexture;
	};

}// namespace hexen::engine::components::graphics
