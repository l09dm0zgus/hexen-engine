//
// Created by cx9ps3 on 04.01.23.
//

#include "SpriteComponent.hpp"
#include <textures/ImageAsset.hpp>

hexen::engine::components::graphics::SpriteComponent::SpriteComponent(const std::shared_ptr<engine::graphics::ImageAsset> &imageAsset)
{
	setTexture(imageAsset);
}

void hexen::engine::components::graphics::SpriteComponent::setTexture(const std::shared_ptr<engine::graphics::ImageAsset> &imageAsset)
{
	mainTexture = imageAsset;
}

std::shared_ptr<hexen::engine::graphics::ImageAsset>hexen::engine::components::graphics::SpriteComponent::getTexture()
{
	return mainTexture;
}
