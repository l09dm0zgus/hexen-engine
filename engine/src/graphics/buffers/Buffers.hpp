//
// Created by cx9ps3 on 06.10.2023.
//

#pragma once
#include <memory_pool/AllocatedObject.hpp>
#include <glm/vec2.hpp>
#include "../profiling/Profiling.hpp"

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
			HEXEN_ADD_TO_PROFILE();
			return elements;
		}

		/**
     	* @brief Constructs a BufferLayout object and initializes it with provided elements.
     	* @param newElements - An initializer list of BufferElements.
     	*/

		BufferLayout(const std::initializer_list<BufferElement> &newElements);

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
			HEXEN_ADD_TO_PROFILE();
			return elements.begin();
		}

		/**
     	* @brief Provides an iterator pointing to the end of the buffer elements.
     	* @returns An iterator to the end of the elements.
     	*/

		std::vector<BufferElement>::iterator end() noexcept
		{
			HEXEN_ADD_TO_PROFILE();
			return elements.end();
		}

		/**
 		 * @brief Pure virtual method that sets the layout of the vertex buffer.
 		 * @param layout The BufferLayout object that defines the new layout of the vertex buffer.
 		 */

		[[nodiscard]] std::vector<BufferElement>::const_iterator begin() const noexcept
		{
			HEXEN_ADD_TO_PROFILE();
			return elements.cbegin();
		}

		/**
   		* @brief This function is used to get a constant iterator pointing to the end of the buffer elements.
   		*
   		* @return A constant iterator to the end of the elements.
   		*/

		std::vector<BufferElement>::const_iterator end() const noexcept
		{
			HEXEN_ADD_TO_PROFILE();
			return elements.cend();
		}

		/**
   		* @brief This function is used to get the stride of the BufferElements
   		*
   		* @return The stride of the BufferElements
   		*/

		[[nodiscard]] core::u32 getStride() const noexcept
		{
			HEXEN_ADD_TO_PROFILE();
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
     	* @return A shared_ptr to the new ElementsBuffer instance.
     	*/

		static std::shared_ptr<ElementsBuffer> create(core::u32 *indices, core::u32 size);

		/**
		 * @brief Static method to create a new instance of ElementsBuffer with dynamic drawning.
		 *
		 * @param size The size of the indices array.
		 * @note correct size is count of indices multiply by sizeof(<indices type>) of indices type.
		 * @return A shared_ptr to the new ElementsBuffer instance.
		 */

		static std::shared_ptr<ElementsBuffer> create(core::u32 size);

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

		/**
		* @brief Pure virtual method that sets data in the elements buffer.
		*/

		virtual void setData(const core::vptr data , core::u32 size) = 0;
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

		virtual ~VertexBuffer() = default;

		/**
        * @brief Static method for creating a vertex buffer.
        * @param vertices A pointer to the array of vertices.
        * @param size The size of the vertex buffer.
        * @return A shared pointer to the created VertexBuffer object.
        */

		static std::shared_ptr<VertexBuffer> create(float *vertices, core::u32 size);

		/**
 		* @brief This function is used to create a vertex buffer of a specified size.
 		*
 		* This function relies on the render API specified in the settings. It asserts that a
 		* render API is set and the PC supports graphics. Currently, it only supports open GL,
 		* other render APIs such as Vulkan and DirectX12 are under development.
 		*
 		* @param size An unsigned 32-bit integer representing the size of the vertex buffer.
 		* @return A shared pointer to the created vertex buffer. If the creation fails or is not supported,
 		*         it returns nullptr.
 		*
 		*/

		static  std::shared_ptr<VertexBuffer> create(core::u32 size);

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

		/**
        * @brief Pure virtual method that sets data in the vertex buffer.
        */

		virtual void setData(const core::vptr data , core::u32 size) = 0;
	};


	/**
 	* @struct FrameBufferSpecification
 	* @brief A structure to represent frame buffer specifications
 	*
 	* This structure has four properties: size, samples and swapChainTarget.
 	*/

	struct FrameBufferSpecification
	{
		/**
    	* @brief Represents the size of the frame buffer.
    	*
    	* The default value is a vector with 1280 by 720 pixels.
    	*/

		glm::vec2 size{1280,720};

		/**
    	* @brief Represents the number of samples in the frame buffer.
    	*
    	* The default value is 1.
    	*/

		core::u32 samples = 1;

		/**
    	* @brief Represents whether this buffer is a swap chain target.
    	*
    	* The default value is `false`.
    	*/

		bool swapChainTarget = false;
	};;

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
     	* @return A std::shared_ptr to the newly created FrameBuffer.
     	*/

		static std::shared_ptr<FrameBuffer> create(const FrameBufferSpecification &specification);

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

		virtual void setSize(const glm::vec2 &size)  = 0;

		/**
 		* @brief Gets the buffer specification.
 		*
 		* @return const hexen::engine::graphics::FrameBufferSpecification& This returns a constant reference to the bufferSpecifications.
 		*
 		* @exception none No exception is thrown.
 		*
 		* @note This function is noexcept, meaning it does not throw exceptions.
 		*/

		[[nodiscard]] virtual const FrameBufferSpecification &getSpecification() const noexcept = 0;

		/**
 		* @brief Gets the value of color attachment object.
 		*
 		* @return hexen::engine::core::u32 This returns the color attachment object as a 32-bit unsigned integer.
 		*
 		* @exception none No exception is thrown.
 		*
 		* @note This function is noexcept, meaning it does not throw exceptions.
 		*/

		virtual core::u32 getColorAttachmentObject() const noexcept = 0;

	};

	/**
 	* @class UniformBuffer
 	* @brief This class extends core::memory::AllocatedObject and provides functionality of a Uniform Buffer.
 	*
	* The objects created by this class can be handled as a Uniform Buffer in graphics cases.
 	*/

	class UniformBuffer : public core::memory::AllocatedObject
	{
	public:
		/**
 		* @brief Destructor for the UniformBuffer class.
 		*/
		virtual ~UniformBuffer() = default;

		/**
 		* @brief Pure virtual function to set data in the UniformBuffer.
 		* @param[in] data Pointer to the data to set in the buffer.
 		* @param[in] size Size of the data to set in the buffer.
 		* @param[in] offset Offset position in the buffer where the data needs to be set.
 		*/
		virtual void setData(const core::vptr data, core::u32 size, core::u32 offset = 0) = 0;

		/**
 		* @brief Static function to create a UniformBuffer instance.
 		* @param[in] size Size of the buffer to create.
		* @param[in] binding The particular binding point where we attach the uniform buffer.
 		* @return A shared pointer to the newly created UniformBuffer instance.
 		*/
		static std::shared_ptr<UniformBuffer> create(core::u32 size, core::u32 binding);
	};

}// namespace hexen::engine::graphics