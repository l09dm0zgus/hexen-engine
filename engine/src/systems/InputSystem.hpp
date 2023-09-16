//
// Created by cx9ps3 on 02.09.2023.
//

#pragma once
#include "../core/memory_pool/AllocatedObject.hpp"
#include <nlohmann/json.hpp>
#include <functional>
#include "../gui/IGUI.hpp"
#include "../core/input_devices/Mouse.hpp"
#include "../core/input_devices/Keyboard.hpp"
namespace hexen::engine::core
{
    class Window;
    namespace input
    {
        class Gamepad;
    }
}

namespace hexen::engine::systems
{
    class InputSystem : public core::memory::AllocatedObject
    {
    private:

        struct ActionMappingCallback
        {

        private:
            std::function<void()> callback;
        public:
            core::u32 playerId;
            std::string name;

            void operator()()
            {
                callback();
            }
        };

        struct AxisMappingCallback
        {

        private:
            std::function<void(float)> callback;
        public:
            core::u32 playerId;
            std::string name;

            void operator()(float value) const
            {
                callback(value);
            }
        };

        using ActionMappingsCallbacks = std::vector<ActionMappingCallback>;
        using AxisMappingCallbacks = std::vector<AxisMappingCallback>;

        std::unique_ptr<core::input::Mouse> mouse;
        std::unique_ptr<core::input::Keyboard> keyboard;
        std::vector<std::shared_ptr<hexen::engine::core::input::Gamepad>> gamepads;

        nlohmann::json keyMappingsFile;

        ActionMappingsCallbacks actionMappingCallbacks;
        AxisMappingCallbacks axisMappingCallbacks;

        std::string path;
        std::vector<std::shared_ptr<gui::IGUI>> guis;

        static constexpr core::u32 MAX_GAMEPAD_AXIS_VALUE = 32767;

        glm::vec2 windowSize{0};
    public:
        struct ActionMapping
        {
            ActionMapping() :sdlKey(0) {};
            ActionMapping(const std::string& name,core::u32 sdlKey,core::u8 playerId = 0) : name(name), sdlKey(sdlKey) , playerId(playerId){};
            core::u32 sdlKey;
            std::string name;
            core::u8 playerId{};
        };

        struct AxisMapping
        {
            AxisMapping() :  sdlKey(0) , value(0.0f) {};
            AxisMapping(const std::string& name,float value,core::u32 sdlKey,core::u8 playerId = 0) : name(name),value(value),sdlKey(sdlKey) ,playerId(playerId) {};
            core::u32 sdlKey;
            float value;
            std::string name;
            core::u8 playerId{};
        };

        void addNewAxisMapping(const std::string& name,float value,core::u32 sdlKey);
        void addNewAxisMapping(const AxisMapping& axisMapping);

        void addNewActionMapping(const std::string& name,core::u32 sdlKey);
        void addNewActionMapping(const ActionMapping& actionMapping);

        void bindAction(const std::string& name,const std::function<void()> &actionCallback);
        void bindAxis(const std::string& name,const std::function<void(float)> &axisCallback);

        void changeMapping(const std::string& name,core::u32, core::u32 newKey);

        explicit InputSystem(const std::string &pathToFile = "mappings.json");
        ~InputSystem() override = default;
        void processInput(const std::shared_ptr<hexen::engine::core::Window> &window);
        void addGUI(const std::shared_ptr<gui::IGUI> &gui);
    private:

        void createMappingsFile();
        void loadMappingsFile();
        std::vector<ActionMapping> actionMappings;
        std::vector<AxisMapping> axisMappings;

        void processKeyboardInput(const SDL_Event &event);
        void processGamepadsInput(const SDL_Event &event);
        void processMouseInput(const SDL_Event &event);

        bool findActionMappingById(core::u32 id,ActionMapping &actionMapping);
        bool findAxisMappingById(core::u32 id,AxisMapping &axisMapping);

        ActionMappingCallback findActionMappingCallback(core::u32 playerId,const std::string &name);
        AxisMappingCallback findAxisMappingCallback(core::u32 playerId,const std::string &name); ;
    };

}
