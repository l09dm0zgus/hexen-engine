//
// Created by cx9ps3 on 27.06.2023.
//

#pragma once

#include "../GUIWindow.h"

namespace edit::gui
{
    class DialogWindow : public GUIWindow
    {
    public:

        enum class Action : core::i32
        {
            PRESSED_OK,
            PRESSED_CANCEL,
            NONE,
            FAILED
        };

        explicit DialogWindow(std::string name);
        Action getLastAction();
        void setOpen(bool newIsOpen);
        void begin() override;
        void end() override;
        void draw() override;
    protected:
        void setAction(Action newAction);
        bool isOpen = false;
        virtual void drawContent() = 0;
    private:
        Action action;
    };
}
