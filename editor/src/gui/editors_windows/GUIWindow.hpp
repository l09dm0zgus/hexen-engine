//
// Created by cx9ps3 on 09.06.2023.
//

#pragma once

#include <core/memory_pool/AllocatedObject.hpp>
#include <glm/vec2.hpp>
#include <imgui.h>
#include <string>

namespace hexen::editor::gui
{
	class Dockspace;
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

	class GUIWindow : public engine::core::memory::AllocatedObject
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

		[[nodiscard]] std::string getName() const noexcept;

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

		template<class T>
		void setSize(T &&newSize)
		{
			size = std::forward<T>(newSize);
		}

		/**
        * @brief Retrieves the size of the window.
        *
        * This function returns the size of the window.
        *
        * @return The size of the window.
        *
        * @note This function is marked as noexcept, indicating that it does not throw any exceptions.
        *
        */

		[[nodiscard]] glm::vec2 getSize() const noexcept;

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
 		* @brief Destructor for the GUIWindow class. It is declared as default and overriden from the parent class.
 		*/

		~GUIWindow() override = default;

		/**
 		* @brief Construct a new GUIWindow object with move semantics for the name field.
 		*
 		* @param name Name of the GUI window. This will be moved into the member variable 'name'.
 		* @param parentDockspace Weak pointer to the parent dockspace object.
 		*
 		* After construction, the HEXEN_ADD_TO_PROFILE() macro is called and the window size is set.
 		*/

		explicit GUIWindow(std::string &&name,const std::weak_ptr<Dockspace> &parentDockspace);

		/**
 		* @brief Construct a new GUIWindow object with copy semantics for the name field.
 		*
 		* @param name Name of the GUI window which will be copied into the member variable 'name'.
 		* @param parentDockspace Weak pointer to the parent dockspace object.
 		*
 		* After construction, the HEXEN_ADD_TO_PROFILE() macro is called and the window size is set.
 		*/

		explicit GUIWindow(const std::string& name, const std::weak_ptr<Dockspace> &parentDockspace);

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
        * @brief Deleted copy constructor for the GUIWindow class.
        *
        * This copy constructor is deleted to prevent the GUIWindow instances
        * from being moved or assigned using the move semantic.
        *
        * @param guiWindow The rvalue reference to the GUIWindow instance.
        * @return Deleted operator - cannot be used.
        *
        * @see GUIWindow
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

		GUIWindow &operator=(GUIWindow &&guiWindow) = delete;

		/**
        * @brief Assignment operator overload for the GUIWindow class.
        *
        * This assignment operator is explicitly deleted to prevent assigning one GUIWindow object to another.
        *
        * @param guiWindow The GUIWindow object to assign.
        * @return None. This assignment operator is deleted.
        */

		GUIWindow &operator=(const GUIWindow &guiWindow) = delete;

		std::string getUUID() const { return UUID;}


		/**
		 * @brief Checks if window open.
		 * This method is virtual.
		 * By default return true.
		 * @return true.
		 */

		virtual bool isOpen();
	protected:
		/**
        * @brief Represents the size of an editor window.
        *
        * The Size class is used to store the dimensions of an object or region in a 2D space. It provides
        * methods for accessing and modifying the width and height values.
        */

		glm::vec2 size {200, 200};
		std::weak_ptr<Dockspace> parentDockspace;

		std::string UUID;

	private:

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


	};
}// namespace hexen::editor::gui
