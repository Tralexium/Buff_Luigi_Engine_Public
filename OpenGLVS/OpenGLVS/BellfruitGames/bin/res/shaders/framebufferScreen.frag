#version 460 core
out vec4 FragColour;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
	float gamma = 2.2; // 2.2 is default for most monitors
	// maybe keep this always..?
	vec3 col = texture(screenTexture, TexCoords).rgb;
    FragColour = vec4(col, 1.0);

	//FragColour.rgb = pow(FragColour.rgb, vec3(1.0/gamma)); // For gamma correction
} 


