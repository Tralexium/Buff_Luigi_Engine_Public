#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoords;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	TexCoords = aTexCoords;	
	
	FragPos = vec3(1 * vec4(aPos, 1.0));   
        
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    Normal = normalize(normalMatrix * aNormal);
	 gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); 
    //gl_Position = model * 2* 2 * vec4(aPos.x, aPos.y, 0.0, 1.0); 
}
