#version 460 core

in vec3 TexCoords;
out vec4 colour;
uniform samplerCube cubemap;

void main() {

colour = texture(cubemap, TexCoords);
}