//
// Created by cx9ps3 on 06.10.2023.
//

#pragma once
#include <core/memory_pool/AllocatedObject.hpp>
#include <glm/vec2.hpp>

namespace hexen::engine::graphics
{
	/**
 	* @enum ShaderDataType
 	* @brief This is an enumeration to represent the various data types used in shaders.
 	*
 	* @var ShaderDataType::NONE
 	* Represents no Shader data type.
 	*
 	* @var ShaderDataType::FLOAT
 	* Represents a single precision floating point data type.
 	*
 	* @var ShaderDataType::INT
 	* Represents an integer data type.
 	*
 	* @var ShaderDataType::BOOL
 	* Represents a boolean data type.
 	*
 	* @var ShaderDataType::VEC2F
 	* Represents a vector with 2 floating point values
 	*
 	* @var ShaderDataType::VEC3F
 	* Represents a vector with 3 floating point values.
 	*
 	* @var ShaderDataType::VEC4F
 	* Represents a vector with 4 floating point values.
 	*
 	* @var ShaderDataType::VEC2I
 	* Represents a vector with 2 integer values.
 	*
 	* @var ShaderDataType::VEC3I
 	* Represents a vector with 3 integer values.
 	*
 	* @var ShaderDataType::VEC4I
 	* Represents a vector with 4 integer values.
 	*
 	* @var ShaderDataType::MAT2
 	* Represents a 2x2 matrix.
 	*
 	* @var ShaderDataType::MAT3
 	* Represents a 3x3 matrix.
 	*
 	* @var ShaderDataType::MAT4
 	* Represents a 4x4 matrix.
 	*/
	enum class ShaderDataType : core::u8
	{
		NONE = 0,
		FLOAT,
		INT,
		BOOL,
		VEC2F,
		VEC3F,
		VEC4F,
		VEC2I,
		VEC3I,
		VEC4I,
		MAT2,
		MAT3,
		MAT4,
	};
	static core::u32 getShaderDataTypeSize(ShaderDataType type);

	/**
 	* @brief A structure to encapsulate a Buffer Element with details related to Shader Data Type.
 	*/

	struct BufferElement
	{
		/// The name of the BufferElement
		std::string name;

		/// The ShaderDataType of the BufferElement
		ShaderDataType type {};

		/// The size of the BufferElement in bytes
		core::u32 size {};

		/// The offset (position) of BufferElement in bytes inside the buffer
		core::u32 offset {};

		/// Boolean flag to determine if the BufferElement has normalization enabled or not
		bool bIsNormalized {false};

		/**
     	* @brief Default constructor.
     	*/

		BufferElement() = default;

		/**
     	* @brief Parameterized constructor.
     	*
     	* @param newType : The ShaderDataType for the BufferElement
     	* @param newName : The name for the BufferElement
     	* @param isNormalized : The normalization status for the BufferElement (False by default)
     	*/

		BufferElement(ShaderDataType newType, const std::string &newName, bool isNormalized = false);

		/**
     	* @brief Getter function for the number of components in BufferElement (i.e. the structure's size).
     	*
     	* @return The size of the structure in bytes
     	*/

		[[nodiscard]] core::u32 getComponentCount() const;
	};

	/**
 	* @class BufferLayout
 	* @brief Class to manage a buffer layout containing multiple BufferElements.
 	*/

	class BufferLayout
	{
	public:
		/**
     	* @brief Retrieves the buffer elements in the layout.
     	* @returns A reference to a vector of BufferElements.
     	*/

		[[nodiscard]] HEXEN_INLINE std::vector<BufferElement> &getElements()
		{
			return elements;
		}

		/**
     	* @brief Constructs a BufferLayout object and initializes it with provided elements.
     	* @param newElements - An initializer list of BufferElements.
     	*/

		BufferLayout(std::initializer_list<BufferElement> &newElements);

		/**
     	* @brief Default constructor
     	*/

		BufferLayout() = default;

		/**
     	* @brief Provides an iterator pointing to the beginning of the buffer elements.
     	* @returns An iterator to the start of the elements.
     	*/

		std::vector<BufferElement>::iterator begin() noexcept
		{
			return elements.begin();
		}

		/**
     	* @brief Provides an iterator pointing to the end of the buffer elements.
     	* @returns An iterator to the end of the elements.
     	*/

		std::vector<BufferElement>::iterator end() noexcept
		{
			return elements.end();
		}

		/**
 		 * @brief Pure virtual method that sets the layout of the vertex buffer.
 		 * @param layout The BufferLayout object that defines the new layout of the vertex buffer.
 		 */

		std::vector<BufferElement>::const_iterator cbegin() noexcept
		{
			return elements.begin();
		}

		/**
   		* @brief This function is used to get a constant iterator pointing to the end of the buffer elements.
   		*
   		* @return A constant iterator to the end of the elements.
   		*/

		std::vector<BufferElement>::const_iterator cend() noexcept
		{
			return elements.end();
		}

		/**
   		* @brief This function is used to get the stride of the BufferElements
   		*
   		* @return The stride of the BufferElements
   		*/

		[[nodiscard]] core::u32 getStride() const noexcept
		{
			return stride;
		}

	private:
		std::vector<BufferElement> elements;///< Stores the elements of the buffer layout.
		core::u32 stride {0};				///< Stores the offset of the elements.

		/**
     	* @brief Calculates the strides and offsets of the buffer elements.
     	*/

		void calculateStridesAndOffsets();
	};

	/**
 	* This class represents a buffer of elements.
 	* @extends core::memory::AllocatedObject
 	* This class provides the means to bind or unbind the elements buffer, and it allows the creation of new ElementsBuffer instances.
 	*/

	class ElementsBuffer : public core::memory::AllocatedObject
	{
	public:
		/**
     	* @brief Default virtual destructor.
     	*
     	*/

		virtual ~ElementsBuffer() = default;

		/**
     	* @brief Static method to create a new instance of ElementsBuffer.
     	*
     	* @param indices Pointer to the list of indices.
     	* @param size The size of the indices array.
     	* @note correct size is count of indices multiply by sizeof(<indices type>) of indices type.
     	* @return A unique_ptr to the new ElementsBuffer instance.
     	*/

		static std::unique_ptr<ElementsBuffer> create(core::u32 *indices, core::u32 size);

		/**
     	* @brief Pure virtual method to bind the elements buffer.
     	*
     	* Details of this method will be determined by the derived class.
     	*/

		virtual void bind() const noexcept = 0;

		/**
     	* @brief Pure virtual method to unbind the elements buffer.
     	*
     	* Details of this method will be determined by the derived class.
     	*/

		virtual void unbind() const noexcept = 0;
	};

	/**
 	* @brief A VertexBuffer class that provides the methods for managing the vertex buffer behavior.
 	* This class is part of the core::memory namespace and inherits from the AllocatedObject class.
 	*/

	class VertexBuffer : public core::memory::AllocatedObject
	{
	public:
		/**
        * @brief Virtual destructor of the VertexBuffer class.
        */

		virtual ~VertexBuffer() = 0;

		/**
        * @brief Static method for creating a vertex buffer.
        * @param vertices A pointer to the array of vertices.
        * @param size The size of the vertex buffer.
        * @return A unique pointer to the created VertexBuffer object.
        */

		static std::unique_ptr<VertexBuffer> create(float *vertices, core::u32 size);

		/**
        * @brief Pure virtual method that binds the vertex buffer.
        */

		virtual void bind() const noexcept = 0;

		/**
        * @brief Pure virtual method that unbinds the vertex buffer.
        */

		virtual void unbind() const noexcept = 0;

		/**
 		 * @brief Pure virtual method that sets the layout of the vertex buffer.
 		 * @param layout The BufferLayout object that defines the new layout of the vertex buffer.
 		 */

		virtual void setLayout(const BufferLayout &layout) = 0;

		/**
 		 * @brief Pure virtual method that gets the layout of the vertex buffer.
 		 * @return The BufferLayout object that defines the layout of the vertex buffer.
 		 */

		[[nodiscard]] virtual const BufferLayout &getLayout() const noexcept = 0;
	};

	/**
 	* @class FrameBuffer
 	* @brief A memory-allocated object that manages a frame buffer.
 	* @details Inherits from the AllocatedObject in the core::memory namespace.
 	*/

	class FrameBuffer : public core::memory::AllocatedObject
	{
	public:
		/**
     	* @brief Factory function to create a new FrameBuffer instance.
     	* @param size A glm::vec2 defining the size of the frame buffer.
     	* @return A std::unique_ptr to the newly created FrameBuffer.
     	*/

		static std::unique_ptr<FrameBuffer> create(const glm::vec2 &size);

		/**
     	* @brief Default destructor.
     	*/

		virtual ~FrameBuffer() = default;

		/**
     	* @brief Pure virtual function to bind the frame buffer.
     	*/

		virtual void bind() const noexcept = 0;

		/**
     	* @brief Pure virtual function to unbind the frame buffer.
     	*/

		virtual void unbind() const noexcept = 0;

		/**
     	* @brief Pure virtual function to set the size of the frame buffer.
     	* @param size A glm::vec2 defining the new size of the frame buffer.
	    */

		virtual void setSize(const glm::vec2 &size) const = 0;

		/**
     	* @brief Pure virtual function to bind the render buffer.
     	*/

		virtual void bindRenderBuffer() = 0;

		/**
     	* @brief Pure virtual function to unbind the render buffer.
     	*/

		virtual void unbindRenderBuffer() = 0;
	};

}// namespace hexen::engine::graphics