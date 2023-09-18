//
// Created by cx9ps3 on 03.09.2023.
//

#pragma once

#include "../core/memory_pool/AllocatedObject.hpp"
#include <SDL_events.h>

namespace hexen::engine::gui
{
	/**
     * @class IGUI
     * @brief Interface for managing widgets on screen.
     *
     * This interface is used in classes that manage widgets on screen.
     * Has one virtual method for processing events from SDL.
     */

	class IGUI : public core::memory::AllocatedObject
	{
	public:
		IGUI() = default;
		IGUI(IGUI &&) = delete;
		~IGUI() override = default;
		IGUI(const IGUI &) = delete;
		IGUI &operator=(IGUI &&) = delete;
		IGUI &operator=(const IGUI &) = delete;
		virtual void processEvent(const SDL_Event &event) = 0;
	};

}// namespace hexen::engine::gui