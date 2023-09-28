//
// Created by cx9ps3 on 09.01.23.
//

#pragma once

#include "../Component.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_SWIZZLE

namespace hexen::engine::components
{
	/**
    * @class TransformComponent
    * @brief Class representing a transform component.
    *
    * The TransformComponent class stores and manages the transformation
    * properties of a game object, such as position, rotation, and scale.
    *
    * The class provides a default constructor that initializes the transform
    * properties to their default values. Additional methods can be added to
    * manipulate and retrieve the transform properties as needed.
    */

	class TransformComponent : public components::Component
	{
	public:

		/**
		 * @brief Generates an empty TransformComponent.
		*/

		TransformComponent() = default;

		/**
 		* - Default destructor.
 		* @brief Destroys the TransformComponent.
 		*/

		~TransformComponent() override = default;

		/**
 		* @brief Explicit constructor that takes a layer as an argument.
 		* @param layer Layer of the transform.
 		*/

		explicit TransformComponent(float layer);

		/**
 		* @brief Explicit constructor that takes a 2D vector position as an argument.
 		* @param newPosition 2D vector new position of the transform.
 		*/

		explicit TransformComponent(const glm::vec2 &newPosition);

		/**
 		* @brief Explicit constructor that takes a 4D matrix transform as an argument.
 		* @param newTransform 4D matrix new transform.
 		*/

		explicit TransformComponent(const glm::mat4 &newTransform);

		/**
 		* @brief Copy constructor.
 		* @param transformComponent The TransformComponent to copy from.
 		*/

		TransformComponent(const TransformComponent &transformComponent);

		/**
 		* @brief Move constructor.
 		* @param transformComponent The TransformComponent to move from.
 		*/

		TransformComponent(TransformComponent &&transformComponent) noexcept;

		/**
 		* @brief Constructor that sets the newPosition and newRotation.
 		* @param newPosition 2D vector new position of the transform.
 		* @param newRotation 2D vector new rotation of the transform.
 		*/

		TransformComponent(const glm::vec2 &newPosition, const glm::vec2 &newRotation);

		/**
 		* @brief Constructor that sets the newPosition, newRotation, and newScale.
 		* @param newPosition 2D vector new position of the transform.
 		* @param newRotation 2D vector new rotation of the transform.
 		* @param newScale 2D vector new scale of the transform.
 		*/

		TransformComponent(const glm::vec2 &newPosition, const glm::vec2 &newRotation, const glm::vec2 &newScale);

		/**
 		* @brief Constructor that sets the newPosition, newRotation, newScale, and layer.
 		* @param newPosition 2D vector new position of the transform.
 		* @param newRotation 2D vector new rotation of the transform.
 		* @param newScale 2D vector new scale of the transform.
 		* @param layer Layer of the transform.
 		*/

		TransformComponent(const glm::vec2 &newPosition, /***/ const glm::vec2 &newRotation, const glm::vec2 &newScale, float layer);

		/**
        * @brief Copy assignment operator for TransformComponent.
        *
        * This assignment operator copy the data from the given lvalue TransformComponent
        * object to this TransformComponent object.
        *
        * @param transformComponent The lvalue TransformComponent object to copy from.
        * @return A reference to this TransformComponent object.
        */

		TransformComponent &operator=(const TransformComponent &transformComponent);

		/**
        * @brief Move assignment operator for TransformComponent.
        *
        * This assignment operator moves the data from the given rvalue TransformComponent
        * object to this TransformComponent object.
        *
        * @param transformComponent The rvalue TransformComponent object to move from.
        * @return A reference to this TransformComponent object.
        */


		TransformComponent &operator=(TransformComponent &&transformComponent) noexcept;

		/**
        * @brief Set the position of the object.
        *
        * This function sets the position of the object using the provided new position.
        * The new position template parameter allows for rvalue references (T&&).
        * The function is declared as noexcept, indicating that it does not throw any exceptions.
        *
        * @tparam T The type for the new position.
        * @param newPosition The new position to be set.
        */

		template<class T>
		void setPosition(T &&newPosition) noexcept;


		/**
        * @brief Sets the rotation to a new value.
        *
        * This function sets the rotation to the provided value. The rotation is represented by the 'newRotation' parameter,
        * which can be of any type T. The rotation value is updated in place.
        *
        * @tparam T   The type of the new rotation value.
        * @param newRotation   The new rotation value to be set.
        *
        * @note The function is marked as noexcept, indicating that it does not throw any exceptions.
        *       This means that it is safe to call this function even in environments with restricted exception handling.
        */

		template<class T>
		void setRotation(T &&newRotation) noexcept;


		/**
        * @brief Sets the scale for the object.
        *
        * This function sets the scale for the object to the specified value. The new scale
        * is passed by rvalue reference, allowing efficient transfer of ownership. The function
        * is marked as noexcept, indicating that it does not throw any exceptions.
        *
        * @param newScale The new scale to set for the object.
        * @tparam T The type of the scale.
        *
        */

		template<class T>
		void setScale(T &&newScale) noexcept;

		/**
        * Sets the layer value of the object.
        *
        * This function updates the layer value of the object
        * to the specified value.
        *
        * @param layer The new layer value for the object.
        * @return void
        *
        * @see getLayer()
        */

		void setLayer(float layer);


		/**
        * @brief Get the layer of the object.
        *
        * This function retrieves the layer of the object. The layer represents the
        * index or level of the object's position in a particular hierarchy or
        * grouping. It helps to define the visual stacking order for rendering or
        * interaction purposes.
        *
        * @return The layer of the object.
        *
        * @note This function is marked as `const` and `noexcept`, which means it
        * does not modify the object's state and it does not throw any exceptions.
        *
        * @sa setLayer()
        */

		[[nodiscard]] float getLayer() const noexcept;


		/**
        * @brief Retrieves the scale of the object.
        *
        * This function returns the scale of the object.
        *
        * @return The scale of the object.
        *
        * @note This function is declared as `const` to indicate that it does not
        * modify the state of the object.
        *
        * @note The function is declared as `noexcept` to specify that it does not
        * throw any exceptions.
        *
        * @see setScale()
        */

		[[nodiscard]] glm::vec2 getScale() const noexcept;


		/**
        * @fn getPosition() const noexcept
        * @brief Retrieves the position of an object.
        *
        * This function returns the current position of an object. The position is a
        * representation of the object's location in a two-dimensional space. The
        * coordinates of the position can be accessed through the x and y properties
        * of the returned value.
        *
        * @return The position of the object.
        *
        * @note This function is declared as const and noexcept, meaning it does not
        *       modify any internal state and guarantees not to throw any exceptions.
        *
        * @see setPosition()
        */

		[[nodiscard]] glm::vec2 getPosition() const noexcept;

		/**
        * @brief Get the rotation of an object.
        *
        * This function returns the rotation of an object. The rotation value is retrieved as a constant reference,
        * ensuring that it cannot be modified externally. The function is marked as noexcept to indicate that it
        * should not throw any exceptions.
        *
        * @return A constant reference to the rotation value.
        */

		[[nodiscard]] glm::vec2 getRotation() const noexcept;


		/**
        * @brief Update the transform matrix.
        *
        * This function updates the transform matrix based on the current transformation
        * parameters such as translation, rotation, and scaling.
        *
        * @note This function assumes that the transformation parameters have been properly set prior to calling it.
        *
        */

		void updateTransformMatrix();

		/**
        * @brief Updates the transform matrix based on the provided parent transform.
        *
        * This function updates the transform matrix of an object based on the provided parent transform.
        * The parent transform is passed as a rvalue reference, indicating that it can be moved from. This
        * allows for efficient update operations.
        *
        * @param parentTransform The parent transform to use for updating the current transform matrix.
        *                        This parameter is a rvalue reference, meaning it can be moved from.
        *
        * @tparam T The type of the parent transform object.
        *
        * @note This function assumes that the current transform matrix and the parent transform
        *       are compatible for the update operation. It is the responsibility of the caller to ensure
        *       this compatibility.
        *
        */

		template<class T>
		void updateTransformMatrix(T &&parentTransform)
		{
			updateTransformMatrix();
			transformMatrix = transformMatrix * std::forward<T>(parentTransform);
		}


		/**
        * @brief Get the transform matrix object.
        *
        * This function retrieves the transformation matrix associated with an object.
        * The matrix represents the transformation of the object from its local space
        * to world space.
        *
        * @return The transform matrix as a constant reference.
        * @note This function does not modify the object's state.
        */

		[[nodiscard]] glm::mat4 getTransformMatrix() const noexcept;


		/**
        * @brief Checks if the object has dirty flag.
        *
        * This method returns a boolean value indicating whether the object has been modified or not.
        *
        * @return True if the object is dirty, false otherwise.
        *
        * @note The isDirty() function is const and noexcept, ensuring that it does not modify the state
        *       of the object and does not throw any exceptions.
        *
        */

		[[nodiscard]] bool isDirty() const noexcept;


		/**
        * @brief Executes the start function.
        *
        * This function implements the start() function of the overridden class.
        * It performs the necessary tasks to start the operation of the program.
        *
        * @details
        * The start() function is responsible for initializing the program and starting its operation.
        * It should be overridden by derived classes to perform any additional setup or initialization
        * required for the specific implementation. The derived class should call the base class's
        * start() function before performing its own setup logic.
        *
        * @remarks
        * This function should be called after all necessary objects and resources have been
        * initialized and configured in the program's main entry point.
        *
        * @note
        * This function is an abstract function and must be overridden in derived classes.
        *
        *
        */

		void start() override;

		/**
        * @brief Updates the object based on the deltaTime.
        *
        * This function is called to update the object's state based on the elapsed time since the last update.
        * The deltaTime parameter represents the time difference between the last frame and the current frame.
        *
        * @param deltaTime The time difference between the last frame and the current frame.
        *
        * @details
        * The update(float deltaTime) function is an override of the base class function and is called from the game loop to
        * update the object's state based on the elapsed time.
        *
        * The deltaTime parameter is a floating-point value representing the time difference between the last frame and the
        * current frame in seconds. It is provided to calculate the time-based changes in the object's state.
        *
        * @note
        * - The deltaTime parameter should always be positive.
        * - The implementation of this function should vary depending on the specific requirements of the object being updated.
        * - Subclasses can override this function to provide custom behavior.
        * - The implementation should consider the deltaTime value to update the object's internal state accordingly.
        */

		void update(float deltaTime) override;

	private:
		/**
        * @brief Moves the transform component into this object.
        *
        * This function moves the given transform component into this object,
        * effectively transferring ownership of the resource from the source
        * object to this object. The source object will be left in a valid
        * but unspecified state afterwards.
        *
        * @param transformComponent The transform component to be moved.
        */

		void move(TransformComponent &&transformComponent) noexcept;


		/**
        * @brief Creates a deep copy of the given TransformComponent object.
        *
        * This function creates a deep copy of the given TransformComponent object and returns
        * the copied object. The deep copy includes copying all the member variables of the
        * original object, ensuring that the copied object is independent and can be modified
        * without affecting the original object.
        *
        * @param transformComponent The TransformComponent object to be copied.
        *
        * @see TransformComponent
        */

		void copy(const TransformComponent &transformComponent);

		/**
        * @brief Rotates a given rotation matrix using rotation angles.
        *
        * This function takes a rotation matrix and rotation angles as input, and returns a
        * new rotation matrix obtained by applying the given rotations.
        *
        * @param rotationMatrix The rotation matrix to be rotated.
        * @param rotation The rotation angles, represented as a 2D vector where x represents
        *                 the rotation angle around the x-axis and y represents the rotation
        *                 angle around the y-axis.
        * @return The resulting rotation matrix after applying the given rotations.
        */

		[[nodiscard]] glm::mat4 rotate(const glm::mat4 &rotationMatrix, /***/ const glm::vec2 &rotation) const;


		glm::mat4 transformMatrix {1.0f};

		glm::vec2 position {0.0f};

		glm::vec2 rotation {0.0f};

		glm::vec2 scale {1.0f};

		float layer {1.0f};

		/**
        * @brief The layerDivider variable represents the value used to divide a layer.
        *
        * The layerDivider is a floating-point variable that determines the division of a layer into multiple sub-layers.
        * It is used in calculations related to layer division.
        *
        * @note The layerDivider value should be a positive floating-point number, which specifies the division factor.
        *
        * @remark The default value of layerDivider is 10.0f.
        *
        */

		const float layerDivider {10.0f};

		/**
        * @brief Indicates whether the variable is dirty or not.
        *
        * This variable is used to track the state of an object or a data value.
        * If the variable is set to true, it means that the object or data value has been modified and it requires updating or saving.
        * If the variable is set to false, it means that the object or data value is up to date and does not require any action.
        *
        * @note By convention, true is used to represent the dirty state and false is used to represent the clean state.
        *
        * @warning Modifying the object or data value while bIsDirty is true without properly handling the consequences may result in undesired behavior.
        */

		bool bIsDirty {true};
	};

}// namespace hexen::engine::components
