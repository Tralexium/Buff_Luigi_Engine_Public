#version 460 core
out vec4 FragColour;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
	
	FragColour = texture(screenTexture, TexCoords);
    float average = 0.2126 * FragColour.r + 0.7152 * FragColour.g + 0.0722 * FragColour.b;
    FragColour = vec4(average, average, average, 1.0);
} 


