#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec4 particlecolor;

// Ouput data
out vec4 FragColour;

uniform sampler2D myTextureSampler;

void main(){
	// Output FragColour = color of the texture at the specified UV
	FragColour = vec4(0.5,0.5,0.5,1)  + 0.5 * texture( myTextureSampler, UV ) * particlecolor;

}