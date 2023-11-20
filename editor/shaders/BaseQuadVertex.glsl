#type vertex
#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTextureCoordinates;
layout (location = 2) in float aTextureIndex;

uniform mat4 view;
uniform mat4 projection;
out float textureIndex;
out vec2 textureCoordinates;

void main()
{
	textureCoordinates = aTextureCoordinates;
	textureIndex = aTextureIndex;
	gl_Position = projection * view * vec4(aPosition,1.0);
}
