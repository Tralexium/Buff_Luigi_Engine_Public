#version 330 core
out vec4 FragColour;

in vec2 TexCoords;
in vec3 Normal;  
in vec3 FragPos;  

struct Light{
	
	vec3 lightDirection;
	vec3 lightPos; 	
	vec3 lightColour;
	vec3 objectColour;
};
  
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;

uniform vec3 viewPos; 
uniform Light light;

void main()
{
	

	//vec3 texturecolor = texture(texture_diffuse1, TexCoords).rgb;

	vec3 norm = Normal;
	norm = texture(texture_normal1, TexCoords).rgb; // normals texture
	norm = normalize(norm * 2.0 - 1.0);  // normalize

    // ambient light
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light.lightColour;
  	
    // diffuse light 
    //vec3 lightDir = normalize(light.lightPos - FragPos);
	vec3 lightDir = normalize(-light.lightDirection);  
    float diff = max(dot(lightDir,norm), 0.0);
    vec3 diffuse = diff * light.lightColour; // TODO SENASTE @NDRING HAR, DE E KNAS
    
    // specular light
    float specularStrength = 0.5; // specular strength
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 reflectDir = reflect(-lightDir, norm);  // 
	vec3 halfwayDir = normalize(lightDir + viewDir);  // blinn-phong
	

    float spec = pow(max(dot(viewDir, halfwayDir), 0.0), 16.0);
    vec3 specular = specularStrength * spec * light.lightColour;  
        
    vec3 result = (ambient + diffuse + specular) * light.objectColour; 
    vec4 FragColour1 = vec4(result, 1.0);
	vec4 FragColour2 = texture(texture_diffuse1, TexCoords);
	
	FragColour = mix(FragColour1, FragColour2, 0.5); // mixing normals and phong
	
	
} 




