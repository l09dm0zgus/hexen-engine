//
// Created by cx9ps3 on 11.06.2023.
//

#pragma once

#include <core/Types.hpp>
#include <core/memory_pool/AllocatedObject.hpp>
#include <string>

namespace hexen::editor::gui
{
	/**
 	* @class INativeFileDialog
 	* @brief This class is responsible for configuring and handling native file dialog interactions.
 	* @details It is an abstract class that defines the basic API for file dialog interactions. It's made for inheritance and must be specifically implemented for each platform.
 	* @note This class follow rule of 5 with all copy and move constructor and assignment operators deleted for avoiding shallow copy.
 	* @note It inherits from engine::core::memory::AllocatedObject, which provides memory management features.
 	*/

	class INativeFileDialog : public engine::core::memory::AllocatedObject
	{
	public:
		/** @brief Default constructor */
		INativeFileDialog() = default;

		/** @brief Default destructor */
		virtual ~INativeFileDialog() = default;

		/** @brief Move constructor (deleted) */
		INativeFileDialog(INativeFileDialog &&) = delete;

		/** @brief Copy constructor (deleted) */
		INativeFileDialog(const INativeFileDialog &) = delete;

		/** @brief Move assignment operator (deleted) */
		INativeFileDialog &operator=(INativeFileDialog &&) = delete;

		/** @brief Copy assignment operator (deleted) */
		INativeFileDialog &operator=(const INativeFileDialog &) = delete;

		/**
     	* @typedef FileFilter
     	* @brief Represents a list of file filters where each filter contains pair of description and pattern.
     	*/

		using FileFilter = std::vector<std::pair<std::string, std::string>>;

		/**
     	* @enum Status
     	* @brief Represents the status of a file dialog operation.
     	*/

		enum class Status : engine::core::i32
		{
			STATUS_OK,	  /**< operation completed successfully */
			STATUS_ERROR, /**< operation encountered an error */
			STATUS_CANCEL /**< operation was cancelled */
		};

		/**
     	* @struct PathSet
     	* @brief Represents a set of file paths.
     	*/

		struct PathSet
		{
			std::vector<std::string> path; /**< list of paths */
			engine::core::i32 count;	   /** number of paths */
		};

		/**
     	* @brief Show an 'Open File' dialog for single file selection.
     	* @param filterList List of filters to use
     	* @param defaultPath Default path to show in the dialog
     	* @param pathToFile Resulting single selected file path
     	* @return The status of the dialog operation
     	* @note pure virtual function
     	*/

		virtual Status openDialog(const FileFilter &filterList, const std::string &defaultPath, std::string &pathToFile) = 0;

		/**
     	* @brief Show an 'Open File' dialog for multiple file selection.
     	* @param filterList List of filters to use
     	* @param defaultPath Default path to show in the dialog
     	* @param pathToFiles Resulting multiple selected file paths
     	* @return The status of the dialog operation
     	* @note pure virtual function
     	*/

		virtual Status openDialog(const FileFilter &filterList, const std::string &defaultPath, PathSet *pathToFiles) = 0;

		/**
     	* @brief Show a 'Save File' dialog.
     	* @param filterList List of filters to use
     	* @param defaultPath Default path to show in the dialog
     	* @param pathToFile Out parameter that gets the full path of the file to be saved
     	* @return The status of the dialog operation
     	* @note pure virtual function
     	*/

		virtual Status saveDialog(const FileFilter &filterList, const std::string &defaultPath, std::string &pathToFile) = 0;

		/**
     	* @brief Show a 'Pick Folder' dialog.
     	* @param defaultPath Default path to show in the dialog
     	* @param pathToFile Out parameter that gets the full path of the folder picked
     	* @return The status of the dialog operation
     	* @note pure virtual function
     	*/

		virtual Status pickDialog(const std::string &defaultPath, std::string &pathToFile) = 0;

		/**
     	* @brief Split a string by a delimiter
     	* @param str String to split
     	* @param delimiter Delimiter to use for splitting
     	* @return A vector of split strings
     	*/

		std::vector<std::string> splitString(const std::string &str, const std::string &delimiter)
		{
			auto s = str;
			std::vector<std::string> splittedString;
			engine::core::i32 position = 0;
			std::string token;
			while ((position = s.find(delimiter)) != std::string::npos)
			{
				token = s.substr(0, position);
				splittedString.push_back(token);
				s.erase(0, position + delimiter.length());
			}
			return splittedString;
		}
	};


}// namespace hexen::editor::gui
