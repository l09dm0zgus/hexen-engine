//
// Created by cx9ps3 on 19.05.2023.
//
#pragma once
#include "../../components/transform/TransformComponent.hpp"
#include "../../core/Types.hpp"
#include "../Entity.hpp"

namespace hexen::engine::entity
{
	/**
 	* @class SceneEntity
 	* @brief This class represents a scene entity in HexenEngine.
 	*
 	* SceneEntity is a type of entity that exists in a scene.
 	* It is a child of the Entity class.
 	*
 	**/

	class SceneEntity : public Entity
	{
	public:

		/**
 		* @brief Constructor that initializes a new SceneEntity object with a given name.
 		* @param name the name of the SceneEntity object
 		*/

		explicit SceneEntity(std::string name);

		/**
 		* @brief Constructor that initializes a new SceneEntity object with a given name and UUID.
 		* @param name the name of the SceneEntity object.
 		* @param UUID the UUID of the SceneEntity object.
 		*/

		SceneEntity(std::string name, const std::string &UUID);

		/**
 		* @brief Gets the name of this SceneEntity.
 		* @returns the name of this SceneEntity.
 		*/

		[[nodiscard]] std::string getName() const noexcept;

		/**
 		* @brief Gets a pointer to the parent scene entity
 		* @returns Pointer to parent SceneEntity, or nullptr if it has no parent
 		*/

		[[nodiscard]] SceneEntity *getParent() const noexcept;

		/**
 		* @brief Sets the parent of this SceneEntity.
 		* @param newParent the new parent of this SceneEntity.
 		*/

		void setParent(SceneEntity *newParent);

		/**
 		* @brief A raw pointer to an object of the TransformComponent class in the components namespace.
 		*/

		components::TransformComponent* transformComponent{nullptr};

		core::i32 handleForTransformComponent{-1};

		/**
 		* @brief Checks if this SceneEntity has any children.
 		* @returns true if this SceneEntity has children, false otherwise.
 		*/

		[[nodiscard]] bool hasChildrens() const noexcept;

		/**
 		* @brief This function gets the children of a SceneEntity in the HexenEngine.
 		*
 		* The children are returned as a HashTable. The keys of this hashtable are strings.
 		* The values are shared pointers to SceneEntity objects.
 		*
 		* @return hexen::engine::core::HashTable<std::string, std::shared_ptr<hexen::engine::entity::SceneEntity>>
 		* Returns a hashtable containing the children of the SceneEntity.
 		*
 		* @exception noexcept This function is specified not to throw any exceptions.
 		*
 		*/

		[[nodiscard]] core::HashTable<std::string, std::shared_ptr<SceneEntity>> getChildrens() const noexcept;

		/**
 		* @brief Retrieves a child of the SceneEntity by name.
 		*
 		* This method retrieves a shared_ptr to a SceneEntity child with the given name.
 		* If no child is found with the given name, this method returns a null shared_ptr.
 		* It is a const and noexcept method, guaranteeing not to modify the object and not to throw any exception.
 		*
 		* @param name Name of the child SceneEntity to be retrieved.
 		*
 		* @return std::shared_ptr<hexen::engine::entity::SceneEntity> Pointer to a child SceneEntity with the given name.
 		*         nullptr if no child was found with that name.
 		*
 		* Usage:
 		* @code
 		*    auto child_entity = scene_entity->getChild("child_1");
 		* @endcode
 		*/

		[[nodiscard]] std::shared_ptr<SceneEntity> getChild(const std::string &name) const noexcept;

		/**
 		* @brief Returns a child SceneEntity by its UUID
 		*
 		* This method gets a child SceneEntity from the children list
 		* based on the provided UUID. If the child does not exist, it will return nullptr.
 		*
 		* @param UUID A const reference to a string containing the UUID of the child SceneEntity.
 		* @return std::shared_ptr<engine::entity::SceneEntity> The child SceneEntity if it exists, nullptr otherwise.
 		* @throw nothrow This function does not throw exceptions.
 		*/

		[[nodiscard]] std::shared_ptr<SceneEntity> getChildByUUID(const std::string &UUID) const noexcept;

		/**
 		* @brief Determines if a child entity with the specified UUID exists in this entity or its children recursively.
 		*
 		* This function will search the direct children first. If not found, it will continue to search the children
 		* of the children until reaching the end of the tree or the descendant is located.
 		*
 		* @param descendantUUID UUID of the descendant to locate.
 		* @return true if the child entity with the specified UUID is found; false otherwise.
 		*/

		bool isDescendantExist(const std::string &descendantUUID);

		/**
	 	* @brief A templated function that renames the current object.
     	*
	 	* This function uses perfect forwarding to accommodate for both lvalue and rvalue arguments,
     	* therefore providing a better flexibility.
	 	*
	 	* @tparam T The type of the argument being passed. Must be compatible with the current object's name.
	 	* @param newName The new name for the current object.
	 	*/

		template<class T>
		void rename(T &&newName)
		{
			HEXEN_ADD_TO_PROFILE();
			name = std::forward<T>(newName);
		}

		//helper static methods for finding nodes in Scene

		/**
 		* @brief Determines if a node with the given UUID exists.
 		*
 		* @param node Shared pointer to a scene entity.
 		* @param UUID UUID to be checked.
 		*
 		* @return Returns 'true' if a node with the given UUID exists and 'false' otherwise.
 		*/

		static bool isNodeExist(const std::shared_ptr<entity::SceneEntity> &node, const std::string &UUID);

		/**
 		* @brief Fetches the node in the scene graph with a given UUID.
 		*
 		* This method attempts to retrieve the SceneEntity node that matches the provided UUID,
 		* scanning through the children of the provided node recursively. The search is depth-first.
 		*
 		* @param node The root node where the search begins.
 		* @param UUID The unique identifier for the SceneEntity we are looking for.
 		*
 		* @return A shared_ptr to the SceneEntity if a node with the provided UUID is found.
 		*         Returns null if no matching SceneEntity is found.
 		*/

		static std::shared_ptr<SceneEntity> getNode(const std::shared_ptr<entity::SceneEntity> &node, const std::string &UUID);

		/**
 		* @brief Searches for a node in the SceneEntity by a specified query.
 		*
 		* This function searches for a node in the SceneEntity by matching
 		* the provided query with the name of the node. If the query matches,
 		* the node is added to a hash table of found nodes and the function
 		* returns true. If the query does not match the name of the node, the
 		* function recursively searches in the children of the current node.
 		*
 		* @param node The shared pointer to the node in the SceneEntity to be searched.
 		* @param searchQuery The query used for searching in the node's name.
 		* @param findedNodes A reference to a hash table where the found nodes are stored.
 		* @return true if a matching node is found; otherwise false.
 		*/

		static bool searchNode(const std::shared_ptr<entity::SceneEntity> &node, const std::string &searchQuery, core::HashTable<std::string, std::shared_ptr<entity::SceneEntity>> &foundedNodes);

		/**
      	* @brief Variadic template function to add a child with provided parameters
	  	*
	  	* This function generates a UUID, creates a shared pointer to a new object of type T initialized with the given parameters,
	  	* and adds it to the 'childrens' map using the generated UUID as a key.
	  	*
        * @tparam T type of the child object to be added
	  	* @tparam Ts types of parameters to be forwarded to the constructor of type T
	  	* @param params parameters to be forwarded to the constructor of type T
	  	*/

		template<class T, class... Ts>
		void addChild(Ts &&...params)
		{
			HEXEN_ADD_TO_PROFILE();
			auto child = core::memory::make_shared<T>(params...);
			child->setParent(this)
;			childrens.set(child->getUUID(), child);
		}


		/**
 		* @brief Adds a child scene entity to the parent scene entity.
 		*
 		* Function to add a child scene entity to its parent scene entity within a scene. The
 		* children are stored in a hashtable where the keys are the UUIDs of the children,
 		* and the values are the shared_ptr to these children.
 		*
 		* @param newChild The shared_ptr to the child scene entity that is to be added.
 		*/

		void addChildByPointer(const std::shared_ptr<SceneEntity> &newChild);

		/**
 		* @brief Forces update of the transform matrix for this SceneEntity.
 		*/

		void forceUpdateTransformMatrix();

		/**
 		* @brief Updates the transformation matrix of the scene entity.
 		*
 		* Checks if the TransformComponent is dirty. If so, it forces an update of the transform matrix.
 		* If not, it loops over the child entities and recursively updates their transform matrices.
 		*/

		void updateTransformMatrix();

		/**
 		* @brief This method changes the parent of a SceneEntity object in
 		* the hexen engine entity.
 		*
 		* This method will check if the new parent is different from the
 		* current parent and it is not the object itself. If the SceneEntity
 		* already has a parent, it will get the child from the old parent with
 		* the same UUID and move it to the new parent. If the SceneEntity
 		* has no parent, it will set itself as a child of the new parent.
 		*
 		* At the end the new parent is set as the parent of the SceneEntity.
 		*
 		* @param newParent A shared pointer to the new parent SceneEntity.
 		*/

		void changeParent(std::shared_ptr<SceneEntity> &newParent);

		/**
 		* @brief Removes the child SceneEntity with the specified name.
 		* @param name the name of the child to be removed.
 		*/

		void removeChild(const std::string &name);

		/**
 		* @brief Removes the child SceneEntity with the specified UUID.
 		* @param UUID the UUID of the child to be removed.
 		*/

		void removeChildByUUID(const std::string &UUID);

	private:

		/**
 		* @brief Holds the name of a Scene Entity object.
 		* This member is used to identify a specific SceneEntity object.
 		*/

		std::string name;

		/**
 		* @brief A Hash Table to hold the children SceneEntity objects.
 		* Key: Name of child entity.
 		* Value: A shared_ptr to child entity.
 		*/

		core::HashTable<std::string, std::shared_ptr<SceneEntity>> childrens;

		/**
 		* @brief A Hash Table to hold the children SceneEntity objects.
	 	* Key: Name of child entity.
 		* Value: A shared_ptr to child entity.
 		*/

		SceneEntity *parent {nullptr};

		/**
 		* @brief A method to find a child SceneEntity by name.
 		*
 		* @param name const string reference which represents the name to search
 		* @return ConstIterator to the child SceneEntity or end() if not found.
 		*/

		[[nodiscard]] core::HashTable<std::string, std::shared_ptr<entity::SceneEntity>>::ConstIterator find(const std::string &name) const;
	};
}// namespace hexen::engine::entity
