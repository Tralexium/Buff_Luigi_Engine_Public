#pragma once
#include "ParticleEmitterComponent.h"
#include "ShaderComponent.h"
#include "CameraComponent.h"
#include "Bitmap.h"
#include <string>

class ParticleSystemRenderer
{
public:

	ParticleSystemRenderer(const unsigned int maxParticles);	
	~ParticleSystemRenderer();
	void initialise();

	void setEmitter(ParticleEmitterComponent* emitter);
	void setCamera(CameraComponent* camera);
	void setTexture(const std::string& textureFilepath);
	void setupVAO();

	void update(float dt);
	void render();

	void resize(unsigned int newSize); // New maximum ammount of particles [globally]
	void updateParticle(Particle& particleData, float dt); // Update the particle position, size and life time.
	void interpolateColor(Particle& particleData); // Interpolates the colors based on the particle's lifetime

	//static unsigned int TextureFromFile(const char* filepath, const std::string& directory, bool gamma = false);

	unsigned int VAO;

private:

	unsigned int m_maxParticles; // Maximum ammount of particles [globally]
	unsigned int m_shaderID; // The shader that's used to render particles.
	unsigned int m_textureID; // Texture of the particle
	unsigned int VBO_billboard; // stays the same for each particle
	unsigned int VBO_positionAndSize; // Current position and size, changes every frame
	unsigned int VBO_color; // Current color, changes every frame
	unsigned int partCounter = 0; // Keeps track of how many live particles get updated

	// Used for passing it to the sub-buffer
	float g_particalPosSizeData[400000];
	unsigned int g_particalColorData[400000];

	ParticleEmitterComponent* m_particleEmitter;
	CameraComponent* m_camera;
	ShaderComponent* m_particleShader;
};
