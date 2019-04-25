#pragma once
#include "ParticleEmitterComponent.h"
#include "ShaderComponent.h"
#include <string>

class ParticleSystemRenderer
{
public:

	ParticleSystemRenderer(const unsigned int maxParticles);

	void setTexture(std::string textureFilepath);
	void initialise();
	void update(Particle* particleData, int numberOfLiveParticles);
	void render(unsigned int numberOfParticles, const unsigned int shaderProgram);
	void setupVAO();

	static unsigned int TextureFromFile(const char* filepath, const std::string& directory, bool gamma = false);

	unsigned int VAO;

private:

	unsigned int m_maxParticles; // Maximum ammount of particles
	unsigned int m_textureIndex; // Texture of the particle
	unsigned int VBO_billboard; // stays the same for each particle
	unsigned int VBO_positionAndSize; // Current position and size, changes every frame
	unsigned int VBO_color; // Current color, changes every frame
};
