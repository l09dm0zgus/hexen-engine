//
// Created by cx9ps3 on 09.06.2023.
//

#pragma once

#include <string>
#include <imgui.h>
#include <core/memory_pool/AllocatedObject.h>
#include <glm/vec2.hpp>

namespace edit::gui
{
    class GUIWindow : public core::mem::AllocatedObject
    {
    public:
        /**
        * @brief Get the name.
        *
        * This function is used to retrieve the name associated with the window.
        *
        * @return The name of the window.
        *
        * @note This function is constant (i.e., does not modify the object) and guaranteed
        *       to not throw any exceptions (noexcept).
        */

        std::string getName() const noexcept;

        /**
        * @brief Sets the size of the window.
        *
        * This function sets the size of the window to the new size passed as an argument.
        * The size is modified in-place.
        *
        * @tparam T Type of the new size.
        * @param newSize The new size to be set.
        *
        * @sa getSize()
        *
        * @note This function allows for both lvalue and rvalue references to the new size.
        */

        template<class T> void setSize(T &&newSize)
        {
            size = std::forward<T>(newSize);
            setWindowSize();
        }

        /**
        * @brief Retrieves the size of the window.
        *
        * This function returns the size of the window.
        *
        * @return The size of the object.
        *
        * @note This function is marked as noexcept, indicating that it does not throw any exceptions.
        *
        */

        glm::vec2 getSize() const noexcept;

        /**
        * @brief Pure virtual function for drawing.
        *
        * This function is a pure virtual function that must be implemented in derived classes.
        * It is responsible for drawing an object to the screen.
        *
        * @note This function does not provide any implementation and must be overridden in derived classes.
        *
    */

        virtual void draw() = 0;

        /**
        * @brief Pure virtual function for the beginning of an drawing editor window.
        *
        *
        * @note This function is declared as pure virtual, which means it must
        * be overridden by any class that inherits from the class that declares
        * this function.
        *
        * @see end()
        */

        virtual void begin() = 0;


        /**
        * @brief A function that signifies the end of an window drawing.
        *
        *
        * @see start()
        */

        virtual void end() = 0;

        /**
        * @class GUIWindow
        * @brief Represents a GUI window.
        *
        * This class provides functionality to create and manage a GUI window.
        * The constructor and destructor are defined with default implementations.
        *
        * It is recommended to inherit from this class and extend it with specific functionality.
        *
        */

        virtual ~GUIWindow() = default;


        /**
        * @class GUIWindow
        * @brief Represents a graphical user interface window.
        *
        * A GUIWindow object is used to display a window in a graphical user interface.
        * It provides methods to set the window's name and perform other related operations.
        */

        explicit GUIWindow(std::string name);

        /**
        * @brief Deleted move constructor for the GUIWindow class.
        *
        * This move constructor is deleted to prevent the GUIWindow instances
        * from being moved or assigned using the move semantic.
        *
        * @param guiWindow The rvalue reference to the GUIWindow instance.
        * @return Deleted operator - cannot be used.
        *
        * @see GUIWindow
        */

        GUIWindow(GUIWindow &&guiWindow) = delete;

        /**
        * @class GUIWindow
        * @brief Represents a GUI window.
        *
        * This class provides functionalities related to GUI windows.
        */

        GUIWindow(const GUIWindow &guiWindow) = delete;

        /**
        * @brief Deleted move assignment operator for the GUIWindow class.
        *
        * This move assignment operator is deleted to prevent the GUIWindow instances
        * from being moved or assigned using the move semantic.
        *
        * @param guiWindow The rvalue reference to the GUIWindow instance.
        * @return Deleted operator - cannot be used.
        *
        * @see GUIWindow
        */

        GUIWindow& operator=(GUIWindow &&guiWindow) = delete;

        /**
        * @brief Assignment operator overload for the GUIWindow class.
        *
        * This assignment operator is explicitly deleted to prevent assigning one GUIWindow object to another.
        *
        * @param guiWindow The GUIWindow object to assign.
        * @return None. This assignment operator is deleted.
        */

        GUIWindow& operator=(const GUIWindow &guiWindow) = delete;
    protected:
    private:

        void setWindowSize();

        /**
        * @brief The name variable stores the name value.
        *
        * The name variable is used to store a string representing a name. It can be used to store the name of a person,
        * an object, or any other entity where a name is relevant. The variable can be accessed and modified throughout the
        * program to perform various operations on the name value.
        *
        * @note The name variable should be initialized with a valid name value before accessing or modifying it.
        */

        std::string name;

        /**
        * @brief Represents the size of an editor window.
        *
        * The Size class is used to store the dimensions of an object or region in a 2D space. It provides
        * methods for accessing and modifying the width and height values.
        */

        glm::vec2 size{200, 200};
    };
}
