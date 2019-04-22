#version 460 core

out vec4 FragColour;

in VS_OUT {
vec3 FragPos; 
vec2 TexCoords;
vec3 TangentLightPos;
//in vec3 Normal;  
vec3 TangentViewPos;
vec3 TangentFragPos;

} fs_in;

struct Light{

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	vec3 lightDirection;
	vec3 lightPos; 	
	vec3 lightColour;
	vec3 objectColour;

	float constant;
    float linear;
    float quadratic;
};

uniform vec3 viewPos; 
uniform Light light;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_displacement1;


vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{ 
   // number of depth layers
    const float minLayers = 8;
    const float maxLayers = 32;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));  
    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.xy / viewDir.z * 0.0015; 
    vec2 deltaTexCoords = P / numLayers;
  
    // get initial values
    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue = texture(texture_diffuse1, currentTexCoords).r;
      
    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture(texture_diffuse1, currentTexCoords).r;  
        // get depth of next layer
        currentLayerDepth += layerDepth;  
    }
    
    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(texture_diffuse1, prevTexCoords).r - currentLayerDepth + layerDepth;
 
    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
} 

void main()
{
	
	vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);


	vec2 texCoords = fs_in.TexCoords;
	texCoords = ParallaxMapping(fs_in.TexCoords, viewDir);

    
	vec3 normal = texture(texture_normal1, texCoords).rgb;
	normal = normalize(normal * 2.0 - 1.0); 


	vec3 ambient = light.ambient * texture(texture_diffuse1, texCoords).rgb;

	vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = light.diffuse * diff *  light.lightColour; // TODO SENASTE @NDRING HAR, DE E KNAS


	//vec3 reflectDir = reflect(-lightDir, normal); 
	vec3 halfwayDir = normalize(lightDir + viewDir);  // blinn-phong
    float spec = pow(max(dot(viewDir, halfwayDir), 0.0), 0.0);
    vec3 specular = light.specular  * spec * light.lightColour; 
	
	vec3 result1 = (ambient + diffuse + specular) * light.objectColour; 
	vec4 FragColour1 = vec4(result1, 1.0);



	// attenuation 
   float distance = length(light.lightPos - fs_in.FragPos);
   float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
   ambient  *= attenuation;  
   diffuse  *= attenuation;
   specular *= attenuation;  

	vec3 result = (ambient + diffuse + specular) * light.objectColour; 
    FragColour = vec4(result, 1.0);


	//FragColour = mix(FragColour1, FragColour2, 0.5);
   
} 


