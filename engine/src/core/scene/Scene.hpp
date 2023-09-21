//
// Created by cx9ps3 on 24.05.2023.
//

#pragma once

#include "../../entity/scene/SceneEntity.h"
#include <functional>
#include <iterator>
#include <vector>

namespace hexen::engine::core
{

	/**
 	* @class Scene
 	* @brief This class represents a scene in the game.
 	*
 	* This class is derived from the AllocatedObject class in the memory namespace. It is used to
 	* manage the various entities and systems that make up a scene in the game.
 	*
 	* @see memory::AllocatedObject
 	*/

	class Scene : public memory::AllocatedObject
	{
	private:

		/**
 		* @brief Represents the size of an entity.
 		* This vector is a 2-dimensional vector where the x-component represents the
 		* width, and the y-component represents the height of the entity.
 		*/

		glm::vec2 size;

		/**
 		* @brief Represents the unit size of an entity.
 		* This is a 2-dimensional vector where the x-component represents the unit
 		* width, and the y-component represents the unit height of the entity.
 		*/

		glm::vec2 unitSize;

		/**
 		* @brief A string containing the name of the entity.
 		*/

		std::string name;

		/**
 		* @brief A smart pointer to the root SceneEntity of this entity.
 		*
 		* This root can be used to traverse the entity hierarchy and perform
 		* operations on all entities in that hierarchy.
 		*/

		std::shared_ptr<entity::SceneEntity> root {};

	public:

		/**
		* @class SceneIterator
		* @brief This class is an iterator for the Scene.
		*
		* This class provides an iterator interface for iterating over
		* the elements of a Scene. This iterator facilitates operations,
		* such as accessing, traversing scenes in a 3D engine.
		*
		* @note Call the methods of this class only after initializing the Scene.
		*
		*/

		class SceneIterator
		{
		protected:

			/**
 			* @brief Holds the index. This value defaults to 0.
 			*/

			u32 index {0};

			/**
 			* @brief A std::vector holding String representation of visited nodes in the Scene.
 			*/

			std::vector<std::string> visitedNode;

			/**
 			* @brief A smart pointer(std::shared_ptr) to an instance of the SceneEntity class. This pointer denotes the root entity in the Scene Tree.
 			*/

			std::shared_ptr<entity::SceneEntity> root;

			friend class Scene;

			/**
 			* @brief Method for traversing a scene-tree.
 			*
 			* This method works recursively, visiting each node in the tree starting from the given node.
 			* Upon visiting, the method checks if the node is already visited. If not, it adds the node
 			* to the list of visited nodes, and continues the traversal through its children.
 			*
 			* @param node Shared pointer to the initial `SceneEntity` object that is the starting point of the traversal.
 			*/

			void traverseTree(const std::shared_ptr<entity::SceneEntity> &node);

		public:

			/**
 			* @brief SceneIterator class constructor used for creating a SceneIterator object.
 			*
 			* @param root A shared pointer to the root entity of the scene.
 			* @param index An unsigned 32 bit integer representing the starting index of the iterator.
 			*
 			* This constructor also initiates a traversal of the scene tree, starting from root.
 			*
 			* @return SceneIterator object.
 			*/

			explicit SceneIterator(const std::shared_ptr<entity::SceneEntity> &root, u32 index);

			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = Scene;
			using difference_type = ptrdiff_t;
			using pointer = const value_type *;
			using reference = const value_type &;

			//create iterator pointing to end()

			/**
 			* @brief Overload of decrement (--) operator for SceneIterator.
 			*
 			* This operator is used to decrement the current index position of the SceneIterator. This function
 			* enables the use of the iterator in a backward manner in the container.
 			*
 			* @return Returns a reference to the updated SceneIterator object.
 			*/

			explicit SceneIterator(const std::shared_ptr<entity::SceneEntity> &root);

			/**
 			* @brief Copy constructor of the SceneIterator class
 			*
 			* @param sceneIterator : A constant reference of SceneIterator object to be copied
 			*/

			SceneIterator(const SceneIterator &sceneIterator) = default;

			/**
 			* @brief Overloaded prefix increment operator for SceneIterator class.
 			*
 			* This function is used to increment the index of the SceneIterator object.
 			* An assertion is made to ensure that the index is not incremented beyond the size of the visited nodes list.
 			*
 			* @return Returns a reference to the SceneIterator object after incrementing the index.
 			*
 			* @pre The index of the SceneIterator must be less than the size of the visited nodes list.
 			* @post The index of the SceneIterator is incremented by 1.
 			*
 			* Example Usage:
 			* @code
 			*   hexen::engine::core::Scene::SceneIterator iter;
 			*   ++iter;
 			* @endcode
 			*
 			* @warning The function will terminate the program if the precondition is not met.
 			*/

			SceneIterator &operator++();

			/**
 			* @brief Overload of decrement (--) operator for SceneIterator.
 			*
 			* This operator is used to decrement the current index position of the SceneIterator. This function
 			* enables the use of the iterator in a backward manner in the container.
 			*
 			* @return Returns a reference to the updated SceneIterator object.
 			*/

			SceneIterator &operator--();

			/**
 			* @brief Postfix increment operator for SceneIterator class.
 			*
 			* This operator creates a copy of the current SceneIterator object, increments this object, then returns the original copy.
 			* The integer argument is a dummy parameter used to differentiate postfix increment from prefix increment.
 			*
 			* @param core::i32 Dummy parameter to differentiate between postfix and prefix increment operator.
 			* @return SceneIterator Returns a copy of the original state of the iterator before the increment.
 			*/

			SceneIterator operator++(i32);

			/**
 			* @brief Pre-decrement overload.
 			* Decrements the SceneIterator and returns a copy of it before the decrement.
 			*
 			* @param val Placeholder parameter, required for pre-decrement operator syntax.
 			* @return Previous value of the SceneIterator.
 			*/

			SceneIterator operator--(i32);

			/**
 			* @brief Overload of the arrow operator for the SceneIterator class.
 			*
 			* This operator is used to return a shared pointer to a SceneEntity object.
 			* The SceneEntity is fetched from the root entity and the visited node at the current index.
 			* Asserts that the current index is less than the size of visited nodes to prevent dereferencing the end iterator.
 			*
 			* @return std::shared_ptr<hexen::engine::entity::SceneEntity> - Shared pointer to the SceneEntity derived from the node at the current index.
 			*/

			std::shared_ptr<entity::SceneEntity> operator->() const;

			/**
 			* @brief Dereference operator for the SceneIterator.
 			*
 			* Overloads the dereference operator to provide a way to access
 			* the SceneEntity currently pointed to by the SceneIterator.
 			*
 			* @return A shared pointer to the SceneEntity that the iterator currently points to.
 			*/

			std::shared_ptr<entity::SceneEntity> operator*() const;

			/**
 			* @brief Overloaded equality operator for SceneIterator class.
 			*
 			* This method checks the equality of two SceneIterator objects by comparing their 'root' and 'index' values.
 			*
	 		* @param sceneIterator The SceneIterator object to compare with.
 			* @return Returns 'true' if the 'root' and 'index' values of both SceneIterators are equal, 'false' otherwise.
 			*/

			bool operator==(const SceneIterator &sceneIterator) const;

			/**
 			* @brief Overloaded equality operator for SceneIterator class.
 			*
 			* This method checks the equality of two SceneIterator objects by comparing their 'root' and 'index' values.
 			*
 			* @param sceneIterator The SceneIterator object to compare with.
 			* @return Returns 'true' if the 'root' and 'index' values of both SceneIterators are equal, 'false' otherwise.
 			*/

			bool operator!=(const SceneIterator &sceneIterator) const;
		};

		/**
 		* @class SceneConstantIterator
 		* @brief A constant iterator for scenes.
 		*
 		* SceneConstantIterator is a type of SceneIterator that disallows modifying the elements it points to.
 		*
 		* @note SceneConstantIterator should be used over SceneIterator when the elements are not intended to be modified.
 		*
 		* @see SceneIterator for the standard iterator that does allow modifying elements.
 		*/

		class SceneConstantIterator : public SceneIterator
		{
		public:

			/**
 			* @brief Initializes a new instance of the SceneConstantIterator class.
 			*
 			* @param root Shared pointer to the root scene entity over which this instance will iterate.
 			* @param index Initial index for the iterator.
 			*/

			explicit SceneConstantIterator(const std::shared_ptr<entity::SceneEntity> &root, u32 index);
			//create iterator pointing to end()

			/**
 			* @brief Construct a new Scene Constant Iterator:: Scene Constant Iterator object
 			*
 			* @param root A shared pointer to the root of the SceneEntity tree that this iterator will traverse.
 			*/

			explicit SceneConstantIterator(const std::shared_ptr<entity::SceneEntity> &root);

			/**
 			* @brief Copy constructor for SceneConstantIterator
 			*
 			* This function utilizes the default copy constructor generated by the compiler.
 			* It deep-copies each field from the input instance to the newly constructed instance.
 			*
 			* @param sceneIterator SceneConstantIterator object to be copied
 			*/

			SceneConstantIterator(const SceneConstantIterator &sceneIterator) = default;

			/**
 			* @brief Overloads the dereference operator "->" for scene constant iterator
 			*
 			* This method overloads the dereference operator. It facilitates
 			* obtaining the SceneEntity object pointer that iterator currently
 			* points to without changing any iterator properties.
 			*
 			* @return std::shared_ptr pointing to the current SceneEntity
 			*/

			const std::shared_ptr<entity::SceneEntity> operator->() const;

			/**
 			* @brief Dereference operator overload
 			*
 			* This function overloads the dereference operator for the SceneConstantIterator class.
 			* It gets the current entity pointed by the iterator.
 			*
 		* @return A shared_ptr to the SceneEntity that the iterator currently points to
 			*/

			const std::shared_ptr<entity::SceneEntity> operator*() const;
		};

		/**
 		* @brief The Scene constructor from the namespace hexen::engine::core
 		*
 		* This method initializes an instance of the Scene class. It takes a name
 		* for the scene and sets up some initial properties like size and unitSize.
 		* Then it immediately creates a root SceneEntity with the same name.
 		* During initialization, other child entities are also temporarily added.
 		*
 		* @note The addition of child entities is only temporary, future versions
 		* will load entities from a file
 		*
 		* @param name A string that will be used as the name of the scene
 		*/

		explicit Scene(const std::string &name);

		/**
 		* @brief Constructs a new Scene object with specified name, size, and unit size.
 		*
 		* This constructor initializes a new Scene with a specific name, size and unit size. It's part of
 		* the hexen::engine::core::Scene class.
 		*
 		* @param name The name of the Scene. It's a string that provides an identification for the Scene object.
 		* @param size The size of the Scene. It's a 2-dimensional glm::vec2 array that defines the width and height of the scene.
 		* @param unitSize The size of a unit in the Scene. It's also a 2-dimensional glm::vec2 array that defines the width and height of a unit in the scene.
 		*
 		*/

		explicit Scene(const std::string &name, const glm::vec2 &size, const glm::vec2 &unitSize);

		/**
 		* @brief Spawns a new entity in the scene.
 		*
 		* This function creates a new entity of type T and adds it as a child
 		* to the root of the scene.
 		* The new entity will have the parameters specified in the function call.
 		* T must be derived from entity::SceneEntity.
 		*
 		* @tparam T Type of the entity to be created. Should be derived from entity::SceneEntity.
 		* @tparam Ts Template parameter pack, representing the types of parameters required to construct an entity of type T.
 		* @param params Parameter pack, representing the actual parameters required to construct an entity of type T.
 		*
 		*/

		template<typename T, std::enable_if_t<std::is_base_of_v<entity::SceneEntity, T>, bool> = true, class... Ts>
		void spawnEntity(Ts &&...params)
		{
			root->addChild<T>(params...);
		}

		/**
 		* @brief Returns the root node of the scene.
 		*
 		* This function retrieves the root node of the scene. The function is marked as noexcept, meaning it
 		* does not throw any exception.
 		*
 		* @return A shared_ptr to the root SceneEntity.
 		*/

		[[nodiscard]] std::shared_ptr<entity::SceneEntity> getRootNode() const noexcept;

		/**
        * Returns an iterator pointing to the first child of the root node in the scene graph.
        *
        * The resulting iterator can be used to traverse the scene graph in a depth-first order.
        *
        * @returns A SceneIterator initialized with the root node and a depth of 0.
        * @note This method is part of the Scene class, which represents the scene graph in the HexenEngine.
        */

		SceneIterator begin();

		/**
 		* @brief This function acts to return the 'end' iterator for a Scene object.
 		*
 		* The Scene::end() method is used to get the end iterator for the Scene object.
 		* The End iterator is typically used with a Begin iterator to iterate over all the elements in a range [Begin, End).
 		* By convention, the End iterator does not point to any element, but a position one step past the last element.
 		* In this case, it will return an iterator initialized with the class's root node.
 		*
 		* @return SceneIterator initialized with the root node of the current Scene object.
 		*/

		SceneIterator end();

		/**
 		* @brief Begins iteration over the scene with a constant iterator.
 		*
 		* This member function returns a constant iterator to the beginning of the scene.
 		* The resulting iterator can be used to sequentially access elements but cannot modify them.
 		*
 		* @return SceneConstantIterator to the first element in the scene. If the scene is empty,
 		* the returned iterator will be equal to end().
 		*/

		[[nodiscard]] SceneConstantIterator cbegin() const;

		/**
 		* @brief Get a constant iterator referring to the end of the scene container in the Hexen engine core.
 		*
 		* This method is part of the hexen::engine::core::Scene class, and is used to create a constant iterator.
 		* This iterator can be used to iterate through the scene objects, but the objects themselves cannot be modified.
 		*
 		* @return hexen::engine::core::Scene::SceneConstantIterator Constant iterator referring to the end of the scene.
 		*/

		[[nodiscard]] SceneConstantIterator cend() const;

		/**
 		* @brief Searches for a scene entity with the given UUID in the Scene.
 		*
 		* This method constructs and returns a SceneConstantIterator to the scene entity
 		* that matches the given UUID. If the entity is not found, the returned iterator will
 		* be equal to `Scene::end()`.
 		*
 		* @param UUID The unique identifier of the entity to find.
 		*
 		* @return SceneConstantIterator to the entity if found, or `Scene::end()` if not found.
 		*
 		* @note The UUID comparison is case-sensitive.
 		*
 		* @see SceneConstantIterator
 		* @see entity::SceneEntity::getNode
 		*/

		[[nodiscard]] SceneConstantIterator find(const std::string &UUID) const;

		/**
 		* @brief A member function that searches for a SceneEntity in the Scene by UUID.
 		* @param UUID The UUID of the SceneEntity to find.
 		* @return A SceneIterator pointing to the SceneEntity with the provided UUID.
 		* If the SceneEntity is not found, the SceneIterator will be end iterator.
 		*
 		* @note This function uses the static function getNode rooted in the SceneEntity class.
 		* The function traverses the Scene graph from the root to the particular node
 		* as identified by its UUID.
 		*
 		*/

		SceneIterator find(const std::string &UUID);

		/**
 		*  @brief Removes a specified object from the scene provided its UUID.
 		*
 		*  @param UUID The UUID of the node in the engine scene to be removed.
 		*
 		*  `hexen::engine::core::Scene::erase` finds an object in the scene by its UUID and
 		*  passes the result to the erase method which removes the object from the scene.
 		*
 		*  Note: If the object isn't found in the scene, the function doesn't perform any actions.
 		*/

		void erase(const SceneIterator &sceneIterator);

		/**
 		* @brief Erases child node from parent scene using SceneIterator.
 		*
 		* This method takes a SceneIterator to a child scene in the parent scene collection, checks if the
 		* iterator is not pointing to end, and if the child scene has a parent. If both conditions are
 		* true, it invokes the removeChildByUUID() method of the parent scene with the UUID of the child scene.
 		*
 		* @param sceneIterator SceneIterator to the child scene to be erased from parent.
 	*/

		void erase(const std::string &UUID);

		/**
 		* @brief Iterates over all entities in the scene, executing a passed function on each.
 		*
 		* This function accepts a callback function and applies it to each entity in the scene. The callback
 		* function should accept a shared pointer to a SceneEntity.
 		*
 		* @param callback The function to apply to each SceneEntity. It should accept a std::shared_ptr to
 		* a entity::SceneEntity.
 		*/

		void forEach(std::function<void(std::shared_ptr<entity::SceneEntity> &)> callback);

		/**
 		* @brief Get the Unit Size object from Scene
 		*
 		* This function retrieves the unit size of the scene.
 		* The function is marked as noexcept, thus it will not throw any exceptions.
 		*
 		* @return glm::vec2 The unit size of the scene in a vec2 format
 		*/

		[[nodiscard]] glm::vec2 getUnitSize() const noexcept;

		/**
 		* @brief Get the Size object
 		*
 		* @return glm::vec2 Returns the size of the scene
 		*
 		* This function returns the current size of the scene. The size is represented as a 2D vector with the x coordinate representing
 		* the width of the scene and the y coordinate representing the height of the scene. The function is declared noexcept which means
 		* it doesn't throw exceptions.
 		*/

		[[nodiscard]] glm::vec2 getSize() const noexcept;
	};

}// namespace hexen::engine::core
