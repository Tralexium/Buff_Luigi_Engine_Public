#version 460 core
out vec4 FragColour;


in vec2 TexCoords;
//in vec3 Normal;  
in vec3 FragPos;  

struct Light{
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 lightPos; 	
	vec3 lightColour;
	vec3 objectColour;
};
  
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;

uniform vec3 viewPos; 
uniform Light light;

float near = 0.1;
float far = 10.0;

float LinearizeDepth(float depth){

	float z = depth* 2.0 - 1.0;
	return (2.0 * near * far)/(far+near -z * (far-near));
}

void main()
{
	
	float depth = LinearizeDepth(gl_FragCoord.z) / far; 

	vec3 norm = texture(texture_normal1, TexCoords).rgb; // normals texture
	norm = normalize(norm * 2.0 - 1.0);  // normalize

    // ambient
    
    vec3 ambient = light.ambient * light.lightColour;
  	
    // diffuse 
    
    vec3 lightDir = normalize(light.lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse * light.lightColour;
    
    // specular
   
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.specular * spec * light.lightColour;  
        
    vec3 result = (ambient + diffuse + specular) * light.objectColour; 
    vec4 FragColour1 = vec4(result, 1.0);
	vec4 FragColour2 = texture(texture_diffuse1, TexCoords);
	
	
	
	vec4 FragColour3 = mix(FragColour1, FragColour2, 0.5); // mixing normals and phong

	vec4 FragColour4 = vec4(vec3(depth), 1.0);

	FragColour = mix(FragColour3, FragColour4, 0.8);
} 