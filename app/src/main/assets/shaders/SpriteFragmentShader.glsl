#version 310 es
precision mediump float;
out vec4 FragColor;
in vec2 textureCoordinate;
uniform sampler2D texture;
void main()
{
    FragColor = texture(texture,textureCoordinates);
}



