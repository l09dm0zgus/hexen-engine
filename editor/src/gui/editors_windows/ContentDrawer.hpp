//
// Created by cx9ps3 on 19.06.2023.
//

#pragma once

#include "../../project/Project.hpp"
#include "AssetsIcon.hpp"
#include "GUIWindow.hpp"
#include "dialogs/CopyingFilesWindow.hpp"
#include "dialogs/DeleteSelectedFilesWindow.hpp"
#include "graphics/textures/GL/GLTexture2D.hpp"

namespace hexen::editor::gui
{
	using FileExtensions = std::unordered_map<std::string, std::filesystem::path>;

	/**
 	* @class AssetExtensions
 	* @brief This class handles the asset extensions.
 	*
 	* This class holds a json file of asset extensions and provides methods
 	* for manipulating it, like getting, adding, checking the existence of extensions,
 	* and retrieving the path to the icons for these extensions.
 	*/

	class AssetExtensions
	{
	private:
		/// @brief Json object representation of an asset extensions file
		nlohmann::json assetExtensionsFile;

		/// @brief Path to the file with extensions.
		std::filesystem::path pathToFileWithExtensions = engine::core::HOME_DIRECTORY / "settings/editor_extensions.json";

		/// @brief Count of extensions in the file.
		engine::core::u32 extensionsCount = 0;

		/// @brief A structure to hold file extensions.
		FileExtensions fileExtensions;

	public:
		/// @brief Default constructor
		AssetExtensions();

		/// @brief Copy constructor
		AssetExtensions(const AssetExtensions &assetExtensions) = default;

		/// @brief Move constructor
		AssetExtensions(AssetExtensions &&assetExtensions) = default;

		/// @brief Copy assignment operator
		AssetExtensions &operator=(const AssetExtensions &assetExtensions) = default;

		/// @brief Move assignment operator
		AssetExtensions &operator=(AssetExtensions &&assetExtensions) = default;

		/// @brief Destructor
		~AssetExtensions();

		/**
    	* @brief Returns the current set of asset extensions.
    	* @return A FileExtensions structure representing the current set of asset extensions.
    	*/

		FileExtensions getAssetExtensions();

		/**
    	* @brief Adds a new asset extension to the collection.
    	* @param fileExtension The file extension to add.
    	* @param pathToIcon The path to the icon that represents this extension.
    	*/

		void addNewAssetExtension(const std::string &fileExtension, const std::filesystem::path &pathToIcon);

		/**
    	* @brief Checks if an extension exists in the collection.
    	* @param fileExtension The file extension to check for.
    	* @return True if the extension exists, false otherwise.
    	*/

		bool isExtensionExist(const std::string &fileExtension);

		/**
    	* @brief Returns the path to the icon for the specified file extension.
    	* @param fileExtension The file extension to get the icon for.
    	* @return The path to the icon for the specified file extension.
    	*/

		std::filesystem::path getPathToIcon(const std::string &fileExtension);
	};
	;

	/**
 	* @class ContentDrawer
 	* @brief A sub-class of GUIWindow for handling operations related to assets.
 	*
 	* Extends the functionality of a GUIWindow to add operations specific to asset handling.
	* This includes operations such as drawing nodes, handling menu interactions, drawing the UI, and more.
 	*/

	class ContentDrawer : public GUIWindow
	{
	private:
		/** @brief Draws a node.
		 * @param i The index of the node to draw.
		 */
		void drawNode(engine::core::i32 i);

		/** @brief Sets the style for a button when it's pressed. */
		void pushButtonStyle();

		/** @brief Reverts the style changes made by pushButtonStyle(). */
		void popButtonStyle();

		/** @brief Displays files in a directory. */
		void showFilesInDirectory();

		/** @brief Resizes the icons. */
		void resizeIcons();

		/** @brief Handles user interactions with the Import New Assets function. */
		void drawImportNewAssets();

		/** @brief Handles user interactions with the Delete function. */
		void drawDelete();

		/** @brief Handles user interactions with the Rename function. */
		void drawRename();

		/** @brief Draws the asset window menu. */
		void drawMenu();

		/** @brief Handles user interactions with the Create New Folder function. */
		void drawNewFolder();

		/** @brief Handles user interactions with the Refresh function. */
		void drawRefresh();

		/** @brief Handles user interactions with the Create Scene function. */
		void drawCreateScene();

		/** @brief Handles user interactions with the Create Tileset function. */
		void drawCreateTileset();

		/** @brief Handles user interactions with the Create Animation function. */
		void drawCreateAnimation();

		/** @brief Handles user interactions with the Create Entity function. */
		void drawCreateEntity();

		/** @brief Reloads the state of the assets window. */
		void refresh();

		/** @brief Retrieves actions from dialog dockedWindows. */
		void getActionsFromDialogs();

		/** @brief Icons for representing assets visually. */
		std::vector<AssetIcon> icons;

		/** @brief The open state of the window. */
		bool isOpen {true};

		/** @brief State if root directory is loaded. */
		bool isRootDirectoryLoaded {false};

		/** @brief Icon size in the window. */
		glm::vec2 iconsSize {64.0f};

		/** @brief Padding size. */
		float padding {16.0f};

		/** @brief List of directories present. */
		std::vector<std::string> directoryList;

		/** @brief The current path that the window is showing. */
		std::filesystem::path currentPath;
		friend class AssetIcon;

		/** @brief The currently selected files. */
		std::vector<std::filesystem::path> selectedFiles;

		/** @brief Callback function when selected files are deleted. */
		std::function<void()> deleteSelectedFilesCallback;

		/** @brief Callback function when refresh is needed. */
		std::function<void()> refreshCallback;

		/** @brief Window for deleting individual files. */
		std::unique_ptr<DeleteFileWindow> deleteFileWindow;

		/** @brief Window for deleting multiple selected files. */
		std::unique_ptr<DeleteSelectedFilesWindow> deleteSelectedFilesWindow;

		/** @brief Window for copying files. */
		std::unique_ptr<CopyingFilesWindow> copyingFilesWindow;

		/** @brief Actions from dialog dockedWindows. */
		std::vector<DialogWindow::Action> dialogWindowActions;

		/** @brief Current hovered icon for asset manipulation. */
		AssetIcon *currentHoveredIcon {nullptr};

		/** @brief The context menu visibility state. */
		bool isShowedContextMenu {false};


		/**
     	* @brief A shared pointer that holds the callbacks for the asset icons.
    	*/

		std::shared_ptr<AssetIconCallbacks> iconCallbacks;

		/**
     	* @brief A map that holds the shared pointers to the textures of the asset's icons.
     	* The key used is the asset name (a string).
     	*/

		std::unordered_map<std::string, std::shared_ptr<hexen::engine::graphics::Texture2D>> iconsTexture;

		/**
     	* @brief This object keeps track of different types of asset extensions and their associated properties.
     	*/

		AssetExtensions assetExtensions;

		/**
     	* @brief The path to the icon representing folders.
     	*/

		std::string pathToFolderIcon = "icons/folder.png";

		/**
     	* @brief The path to the icon representing general files.
     	*/

		std::string pathToFileIcon = "icons/file.png";

		/**
 		* @brief Retrieves the texture ID for an icon associated with a specific file extension, creating a new texture if necessary.
 		*
 		* This function attempts to find a previously created texture for a file extension. If it does not exist, it creates a new texture for the
 		* icon associated with the file type, registers it against the extension, and returns its ID. If a texture already exists, it simply returns
 		* its ID.
 		*
 		* @param[in] extension A string that represents the file extension for which the icon texture ID is needed.
 		* @param[in] pathToAsset A filesystem path that represents the location of the asset.
 		* @param[in] pathToIcon A filesystem path that represents the location of the icon.
 		*
 		* @return Returns the ID of the icon texture associated with the specified file extension.
 		*
 		* @note This function may create a new texture for an icon associated with the specified file extension if one does not already exist.
 		*/

		engine::core::u32 getIconTextureID(const std::string &extension, const std::filesystem::path &pathToAsset, const std::filesystem::path &pathToIcon);

		/**
 		* @brief Initialize method for the ContentDrawer class.
 		*
 		* This method performs the following tasks:
 		*   1. Set the size of the ContentDrawer to 1280x400 units.
 		*   2. Create objects for dealing with asset icons, file deletions, selected file deletions, and file copying.
 		*   3. Define a callback for deleting selected files.
 		*   4. Define a refresh callback that refreshes the content.
 		*   5. Add a global shortcut for refreshing the content.
 		*
 		* @note It's invoked by HEXEN_ADD_TO_PROFILE() macro.
 		*/

		void initialize();

	public:
		/**
 		* @brief This is the constructor for the ContentDrawer class that takes rvalue reference of name.
 		* The constructor initializes the GUIWindow with given name and parentDockspace.
 		* After initialization, it makes a call to the initialize function of the class.
 		*
 		* @param name Rvalue reference to the name of the ContentDrawer
 		* @param parentDockspace The weak_ptr to the Dockspace that is the parent for this ContentDrawer
 		*/

		explicit ContentDrawer(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace);

		/**
 		* @brief This is the constructor for the ContentDrawer class that takes const reference of name.
 		* The constructor initializes the GUIWindow with given name and parentDockspace.
 		* After initialization, it makes a call to the initialize function of the class.
 		*
 		* @param name Const reference to the name of the ContentDrawer
 		* @param parentDockspace The weak_ptr to the Dockspace that is the parent for this ContentDrawer
 		*/

		explicit ContentDrawer(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace);

		/** @brief Begins drawing of the window. Overrides the function in GUIWindow. */
		void begin() override;

		/** @brief Handles drawing of the window. Overrides the function in GUIWindow. */
		void draw() override;

		/** @brief Ends drawing of the window. Overrides the function in GUIWindow. */
		void end() override;

		/**
 		* @brief Adds a new icon corresponding to asset extension.
 		*
 		* This function adds a new asset extension with its corresponding icon path. It also assigns a callback
 		* function that will be triggered when the asset with the specified extension is interacted with.
 		* The icon paths and the callbacks are stored in under `assetExtensions` and `iconCallbacks` objects
 		* respectively.
 		*
 		* @param extension    The extension for the asset whose icon is to be added.
 		* @param pathToIcon   The path to the icon of the asset.
 		* @param iconCallback The callback function to be associated with the asset extension.
 		*/

		void addNewIcon(const std::string &extension, std::filesystem::path &pathToIcon, const std::function<void(const std::filesystem::path &path)> &iconCallback);
	};
}// namespace hexen::editor::gui