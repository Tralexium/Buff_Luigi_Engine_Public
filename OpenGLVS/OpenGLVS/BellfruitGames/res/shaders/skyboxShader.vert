#version 460 core

layout (location = 0) in vec3 position;
out vec3 TexCoords;

uniform mat4 Vskybox;
uniform mat4 P;

void main(){

gl_Position = P * Vskybox * vec4(position, 1.0);

TexCoords = position;

}