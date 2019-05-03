#version 330 core
out vec4 FragColour;
out vec4 FragColour2;
out vec4 FragColour3;
out vec4 FragColour4;
out vec4 BrightColour;

//vec3 result;
//vec3 result2;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D image;
uniform sampler2D bloomBlur;
uniform float exposure;

uniform bool horizontal;
uniform float kernel[11] = float[] (0.0093, 0.028002, 0.065984, 0.121703, 0.175713, 0.198596, 0.175713, 0.121703, 0.065984, 0.028002, 0.0093);

void brightFilter()
{
	vec3 hdrCol = texture(screenTexture, TexCoords).rgb;
	FragColour = vec4(hdrCol, 1.0);
    float brightness = dot(FragColour.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColour = vec4(FragColour.rgb, 1.0);
	else
		BrightColour = vec4(0.0, 0.0, 0.0, 1.0);
}


void blur()
{	          
     vec2 tex_offset = 1.0 / textureSize(image, 0); // gets size of single texel
     vec3 result1 = texture(image, TexCoords).rgb * kernel[0];
	 
         for(int i = -5; i <= 5; ++i)
         {
            result1 += texture(image, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * kernel[i];
            result1 += texture(image, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * kernel[i];
         }
     
    
   
         for(int i = -5; i <= 5; ++i)
         {
             result1 += texture(image, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * kernel[i];
             result1 += texture(image, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * kernel[i];
         }
		 FragColour = vec4(result1, 1.0);
		 float brightness = dot(FragColour.rgb, vec3(0.2126, 0.7152, 0.0722));
		 if(brightness > 1.0)
			BrightColour += vec4(FragColour.rgb, 1.0);
		
}

void HDR()
{
	const float gamma = 2.2;
    vec3 hdrColour = texture(screenTexture, TexCoords).rgb;      

    // tone mapping
    vec3 result2 = vec3(1.0) - exp(-hdrColour * 2.0);
    // also gamma correct while we're at it       
    result2 = pow(result2, vec3(1.0 / gamma));
	FragColour = vec4(result2, 1.0);
	BrightColour += vec4(FragColour.rgb, 1.0);
		
}

void main()
{	
	brightFilter();
	blur();
	HDR();
} 


