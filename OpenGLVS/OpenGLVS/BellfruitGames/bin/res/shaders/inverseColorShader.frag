#version 460 core
out vec4 FragColour;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
	 FragColour = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);

} 
