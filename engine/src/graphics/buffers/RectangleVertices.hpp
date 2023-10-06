//
// Created by cx9ps3 on 02.01.23.
//

#pragma once

namespace hexen::engine::graphics
{
	enum RectangleDataSizes
	{
		/**
        * @brief The size of the vertices array.
        *
        * This variable represents the size of the vertices array, which is used to store vertices for procedural generation or rendering.
        * The value of this variable is defined as 12.
         *
        */

		VERTICES_ARRAY_SIZE = 12,

		/**
        * @brief The maximum size of the indices array.
        *
        * This constant defines the maximum size of the indices array used in the program.
        * The indices array is used to store a series of indices to access elements in another array or container.
        * The size of the array is fixed to ensure efficient memory usage and avoid potential buffer overflows.
        *
        * It is highly recommended to use this constant instead of hardcoding the array size to ensure consistency and readability of the code.
        * If you need to increase the size of the array, you should update this constant accordingly.
        *
        * @note This constant should not be modified at runtime as it may lead to unexpected behavior.
        *
        * @ref IndicesArrayExample provides an example usage of this constant.
        */

		INDICES_ARRAY_SIZE = 6
	};
	struct RectangleVertices
	{
		/**
        * @brief The array of vertices for a rectangle.
        *
        * This array represents the 3D coordinates of the vertices for a rectangle in 3D space.
        * It is defined as a static array with a fixed size, specified by the RectangleDataSizes::VERTICES_ARRAY_SIZE constant.
        *
        * The coordinates of each vertex are represented as floats and are organized as follows:
        * - The first vertex is located at index 0 and contains the x, y, and z coordinates.
        * - The second vertex is located at index 1 and contains the x, y, and z coordinates.
        * - The third vertex is located at index 2 and contains the x, y, and z coordinates.
        * - The fourth vertex is located at index 3 and contains the x, y, and z coordinates.
        *
        * The order of the vertices in the array determines the order in which they will be rendered when
        * creating a rectangle shape using these vertices.
        *
        * @note The coordinates are specified in a right-handed coordinate system, where the positive x-axis
        * points to the right, the positive y-axis points upward, and the positive z-axis points towards the viewer.
        *
        *
        * @see RectangleDataSizes
        */

		const float vertices[RectangleDataSizes::VERTICES_ARRAY_SIZE] =
				{
						-1.0f, -1.0f, -0.0f,
						1.0f, 1.0f, -0.0f,
						-1.0f, 1.0f, -0.0f,
						1.0f, -1.0f, -0.0f};

		/**
        * @brief Array representing the indices of a rectangle.
        *
        * This array defines the order in which the vertices of a rectangle are connected to draw it.
        *
        * The indices array has a fixed size indicated by RectangleDataSizes::INDICES_ARRAY_SIZE.
        * It contains six elements that represent the vertices of two triangles forming the rectangle.
        * Each vertex is represented by an index corresponding to its position in the vertex array.
        *
        * The order of the indices determines the winding order of the triangles, which affects how the
        * rectangle is rendered.
        *
        * The format of the indices array is as follows:
        * - First triangle indices : 0, 1, 2
        * - Second triangle indices: 0, 3, 1
        *
        */

		const core::u32 indices[RectangleDataSizes::INDICES_ARRAY_SIZE] =
				{
						0, 1, 2,
						0, 3, 1};
	};
}// namespace hexen::engine::graphics::gl
