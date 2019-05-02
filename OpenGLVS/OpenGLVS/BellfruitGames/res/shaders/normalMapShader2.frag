#version 330 core
out vec4 FragColour;

in vec2 TexCoords;
in vec3 Normal;  
in vec3 FragPos;  

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
  
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;

uniform vec3 viewPos; 
uniform Light light;

void main()
{
	
	vec3 norm = Normal;
	norm = texture(texture_normal1, TexCoords).rgb; // normals texture
	norm = normalize(norm * 2.0 - 1.0);  // normalize

    // ambient light
    vec3 ambient = light.ambient * texture(texture_diffuse1, TexCoords).rgb;
  	
    // diffuse light 
	vec3 lightDir = normalize(-light.lightDirection);  // Directional	
	//vec3 lightDir = normalize(light.lightPos - FragPos); // Point

    float diff = max(dot(lightDir,norm), 0.0);
    vec3 diffuse = light.diffuse * diff *  light.lightColour; // TODO SENASTE @NDRING HAR, DE E KNAS
    
    // specular light
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  // 
	vec3 halfwayDir = normalize(lightDir + viewDir);  // blinn-phong
    float spec = pow(max(dot(viewDir, halfwayDir), 0.0), 0.0);
    vec3 specular = light.specular  * spec * light.lightColour;  

	// attenuation 
    float distance = length(light.lightPos - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    ambient  *= attenuation;  
    diffuse  *= attenuation;
    specular *= attenuation;  
	

	// FINAL COLOUR
    vec3 result = (ambient + diffuse + specular) * light.objectColour; 
    FragColour = vec4(result, 1.0);

} 




