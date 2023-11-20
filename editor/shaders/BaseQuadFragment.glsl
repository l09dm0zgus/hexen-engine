#type fragment
#version 460 core
out vec4 FragColor;

in float textureIndex;
in vec2 textureCoordinates;
uniform sampler2DArray textures;

void main()
{
	FragColor = texture(textures, vec3(textureCoordinates.xy,textureIndex));
}
