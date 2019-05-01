#version 330 core
out vec4 FragColour;



out vec3 result1;
out vec3 result2;

in vec2 TexCoords;
//in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;
uniform vec3 lightColour;


uniform sampler2D screenTexture;
uniform sampler2D bloomBlur;
uniform bool bloom;
uniform float exposure;

uniform bool horizontal;
uniform float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

void blur()
{
		vec2 tex_offset = 1.0 / textureSize(screenTexture, 0); // gets size of single texel
		 result1 = texture(screenTexture, TexCoords).rgb * weight[0];
		if(horizontal)
		{
			for(int i = 1; i < 5; ++i)
			{
				result1 += texture(screenTexture, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
				result1 += texture(screenTexture, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
			}
		}
		else
		{
			for(int i = 1; i < 5; ++i)
			{
				result1 += texture(screenTexture, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
				result1 += texture(screenTexture, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
			}
		}
		
}

void glow()
{
		const float gamma = 2.2; // 2.2 is default for most monitors
		// maybe keep this always..?
		vec3 hdrCol = texture(screenTexture, TexCoords).rgb;
		vec3 bloomCol = texture(bloomBlur, TexCoords).rgb;
	
		if(bloom)
		{
			hdrCol += bloomCol; // additive blending
			// tone mapping
			 result2 = vec3(1.0) - exp(-hdrCol * exposure);
			// also gamma correct while we're at it       
			result2 = pow(result2, vec3(1.0 / gamma));
		}
		else
		{
			result2 = pow(hdrCol, vec3(1.0 / gamma));
		}
}


void main()
{
	//brightFilter();
	blur();
	glow();
	FragColour =  vec4((result1+result2), 1.0);

} 


