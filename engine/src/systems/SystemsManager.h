//
// Created by cx9ps3 on 13.07.2023.
//
#pragma once
#include "../core/memory_pool/AllocatedObject.h"
#include "IRenderSystem.h"
#include "IGamePlaySystem.h"
namespace hexen::engine::core
{
    class Window;
}

namespace hexen::engine::systems
{
    class SystemsManager : public hexen::engine::core::memory::AllocatedObject
    {
    private:

        /**
        * @brief Represents the current system manager.
        *
        * The currentSystemManager variable is used to keep track of the active system manager within the software application.
        * It allows access to various functionalities and resources provided by the system manager.
        */

        static SystemsManager* currentSystemManager;


        /**
         * @brief The number of components.
         *
         * This variable represents the number of components. It is initialized to zero.
         * Use this variable to keep track of the number of components in your program.
         *
         */

        core::i32 numberOfComponents{0};

        /**
        * @brief The collection of rendering systems.
        *
        * This variable represents a collection of rendering systems used in the application.
        * Each rendering system is responsible for rendering specific components of the scene.
        * The collection allows for managing and interacting with the rendering systems as a whole.
        *
        * The rendering systems can be accessed, added, removed, and modified using the methods
        * provided by the collection. It provides a convenient abstraction for working with
        * multiple rendering systems simultaneously.
        *
        */

        std::vector<std::unique_ptr<IRenderSystem>> renderSystems;

        /**
        * @brief This variable holds the list of gameplay systems.
        *
        * It represents the collection of different systems involved in the gameplay of the game.
        * Each gameplay system is responsible for a specific aspect of the game, such as AI, player controls, physics, etc.
        *
        * This variable should be initialized and populated with gameplay system instances before starting the game.
        * It can be accessed to retrieve or manipulate individual gameplay systems as per the game requirements.
        *
        */

        std::vector<std::unique_ptr<IGamePlaySystem>> gameplaySystems;

    public:

        /**
        * @brief Processes the input from a given window.
        *
        * This function processes the input from a specified window and performs any necessary actions based on the input.
        *
        * @param window The window from which the input will be processed.
        */

        virtual void processInput(const std::shared_ptr<core::Window> &window);


        /**
         * @brief Starts all systems,called before main loop.
         */

        virtual void start();


        /**
         * @brief Calling render() in all render systems
         *
         * @param alpha interpolated value for correct position of rendered object.
         */

        virtual void render(float alpha);

        /**
         * @brief Updates the game play systems.
         *
         * @param deltaTime The time interval between the current and previous frame.
         *
         * @note This function should be called every frame to ensure the variable is
         *       updated according to the time elapsed.
         *
         * @warning The deltaTime should be a positive value for accurate updates.
         *
         */

        virtual void update(float deltaTime);

        /**
         * @brief Construct and initialize a new game play system in current system manager.
         *
         * This constructor takes any number of arguments of type `Args`. These arguments
         * are used to initialize the game play system. You can pass any appropriate
         * arguments required for the game play system.
         *
         * @param args The arguments required to initialize the game play system.
         * @tparam Args The type(s) of the arguments passed. These can be any valid types
         *              required for the game play system initialization.
         * @tparam T  Type based on IGamePlaySystem class.
         */

        template<class T,typename ...Args> HEXEN_INLINE static void addGamePlaySystem(Args... args)
        {
            if(currentSystemManager != nullptr)
            {
                currentSystemManager->gameplaySystems.emplace_back(core::memory::make_unique<T>(args...));
            }
        }

        /**
       * @brief Construct and initialize a new render system.
       *
       * This constructor takes any number of arguments of type `Args`. These arguments
       * are used to initialize the game play system. You can pass any appropriate
       * arguments required for the game play system.
       *
       * @param args The arguments required to initialize the render system.
       * @tparam Args The type(s) of the arguments passed. These can be any valid types
       *              required for the game play system initialization.
       * @tparam T  Type based on IRenderSystem class.
       */

        template<class T,typename ...Args> HEXEN_INLINE static void addRenderSystem(Args... args)
        {
            if(currentSystemManager != nullptr)
            {
                currentSystemManager->renderSystems.emplace_back(core::memory::make_unique<T>(args...));

            }
        }

        /**
         * @brief Sets the current system manager.
         *
         * This function allows the user to set the current system manager
         *
         * @param systemManager A pointer to the system manager object.
         */

        HEXEN_INLINE static void setCurrentSystemManager(SystemsManager* systemManager)
        {
            currentSystemManager = systemManager;
        }


        /**
        * @brief Default virtual destructor.
        */

        ~SystemsManager() override = default;

    };
}




