//
// Created by cx9ps3 on 17.09.2023.
//

#include "InputHelper.hpp"
#include "SystemsManager.hpp"
#include "InputSystem.hpp"

void hexen::engine::input::InputHelper::bindAction(const std::string &name, const std::function<void()> &actionCallback,bool enableForMultiplePLayers)
{
    getInputSystem()->bindAction(name, actionCallback, enableForMultiplePLayers);
}

std::shared_ptr<hexen::engine::systems::InputSystem> hexen::engine::input::InputHelper::getInputSystem()
{
    auto manager = systems::SystemsManager::getCurrentSystemManager();
    HEXEN_ASSERT(manager != nullptr, "SystemsManager is nullptr");

    auto  inputSystem = manager->getInputSystem();
    HEXEN_ASSERT(inputSystem != nullptr, "InputSystem is nullptr");
}

void
hexen::engine::input::InputHelper::bindAxis(const std::string &name, const std::function<void(float)> &axisCallback, bool enableForMultiplePLayers)
{
    getInputSystem()->bindAxis(name, axisCallback, enableForMultiplePLayers);
}
