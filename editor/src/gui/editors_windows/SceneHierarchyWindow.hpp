//
// Created by cx9ps3 on 28.06.2023.
//

#pragma once

#include "GUIWindow.hpp"
#include "entity/scene/SceneManager.hpp"

namespace hexen::editor::gui
{
	/**
 	* @class SceneHierarchyWindow
 	* @brief Class for creating and managing a scene hierarchy window.
 	* @details This class provides functionality for creating, handling drag and drop, and drawing a scene hierarchy window in a HexenEngine's graphical user interface.
 	* @inherits GUIWindow
 	*/

	class SceneHierarchyWindow : public GUIWindow
	{
	private:
		/**
		 * 	@brief Flag indicating whether the window is open (true) or closed (false).
		 */

		bool isOpen {true};

		/**
     	* @brief Draw the child entities of the current entity.
     	* @param childs A hash table of string and shared pointer pairs to SceneEntity objects.
     	*/

		void drawEntityChilds(hexen::engine::core::HashTable<std::string, std::shared_ptr<hexen::engine::entity::SceneEntity>> &&childs);

		/**
     	* @brief Draw the provided entity.
     	* @param entity A shared pointer to the SceneEntity object to draw.
     	*/

		void drawEntity(const std::shared_ptr<hexen::engine::entity::SceneEntity> &entity);

		/**
     	* @brief Start a drag and drop operation with the given entity as the source.
     	* @param sceneEntity A shared pointer to the SceneEntity object to start drag and drop.
     	*/

		void startDragAndDropSource(const std::shared_ptr<hexen::engine::entity::SceneEntity> &sceneEntity);

		/**
     	* @brief Start a drag and drop operation with the given entity as the target.
     	* @param sceneEntity A shared pointer to the SceneEntity object to start drag and drop.
     	*/

		void startDragAndDropTarget(std::shared_ptr<hexen::engine::entity::SceneEntity> &&sceneEntity);

		/**
		 * @brief Draw the search bar in the window.
		 */

		void drawSearchBar();

		/**
		 * @brief Draw context menu in the window.
		 */
		void drawContextMenu();

		/**
		 * @brief Draw the Scene entity addition section in the window.
		 */
		void drawAddSceneEntity();

		/**
		 * 	@brief Draw the child entity addition section in the window.
		 */
		void drawAddChild();

		/**
		 * @brief Draw the delete section in the window.
		 */
		void drawDelete();

		/**
		 * @brief Check which item is currently being hovered over by the mouse cursor.
		 */

		void checkHoveredItem();

		/**
		 * @brief Shared pointer to the scene.
		 */
		std::shared_ptr<hexen::engine::core::Scene> scene;

		/**
		 * @brief Shared pointer to the node being hovered.
		 */
		std::shared_ptr<hexen::engine::entity::SceneEntity> hoveredNode;

		/**
		 * @brief Search query text.
		 */
		std::string searchQuery;

		/**
		 * @brief Hash table containing the founded child entities.
		 */
		hexen::engine::core::HashTable<std::string, std::shared_ptr<hexen::engine::entity::SceneEntity>> foundedChilds;

		/**
		 * @brief Hash table indicating by name if a node is being edited currently.
		 */
		hexen::engine::core::HashTable<std::string, bool> isNodeNameEditing;

		/**
		 * @brief The name of the payload for drag and drop operations.
		 */
		const std::string PAYLOAD_NAME {"SCENE_HIERARCHY_PAYLOAD"};

		/**
		 *  @brief Flag to indicate if an item is currently being hovered over by the mouse cursor.
		 */
		bool isItemHovered {false};

		bool isActiveNodePopUp {false};

		/**
 		* @brief Initialize the SceneHierarchyWindow.
 		*
 		* This function sets the size of SceneHierarchyWindow, loads
 		* the scene using SceneManager and sets the current scene.
 		*/

		void initialize();

	public:

		/**
 		* @brief Constructor of SceneHierarchyWindow class using move semantics.
 		* @param name Name of the Scene Hierarchy Window.
 		* @param parentDockspace A reference to the Dockspace of the Window.
 		*
 		* This function initializes an instance of the SceneHierarchyWindow class,
 		* moves the parameter 'name' to the class member and sets a weak_ptr to
 		* the parent Dockspace.
 		*/

		SceneHierarchyWindow(std::string&& name, const std::weak_ptr<Dockspace> &parentDockspace);

		/**
 		* @brief Constructor of SceneHierarchyWindow class.
 		* @param name Name of the Scene Hierarchy Window.
 		* @param parentDockspace A reference to the Dockspace of the Window.
 		*
 		* This function initializes an instance of the SceneHierarchyWindow class,
 		* copies the parameter 'name' to the class member and sets a weak_ptr to
 		* the parent Dockspace.
 		*/

		SceneHierarchyWindow(const std::string& name, const std::weak_ptr<Dockspace> &parentDockspace);

		/**
		 * @brief Method to initialize the window.
		 */
		void begin() override;

		/**
		 * @brief Draw the window and its content.
		 */
		void draw() override;

		/**
		 * @brief Close the window and perform cleanup tasks.
		 */
		void end() override;
	};
}// namespace hexen::editor::gui
