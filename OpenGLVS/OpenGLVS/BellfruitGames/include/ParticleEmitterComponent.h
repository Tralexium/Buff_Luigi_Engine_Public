#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

struct Particle
{
	// initialised to dead particle (-1.0f life)
	Particle() : life(0.0f), size(1.0f), colour(1.0f, 0.0f, 0.0f, 1.0f), velocity(0.0f, 0.0f, 0.0f) {}

	// variables that need passing to the shader
	float life, size, cameraSqDistance;
	glm::vec3 position, velocity;
	glm::vec4 colour, finalColour;

	// sort to ensure the particles further away are drawn first
	bool operator<(const Particle& that) const
	{
		return this->cameraSqDistance > that.cameraSqDistance;
	}
};

class ParticleEmitterComponent : public Component
{
private:
	unsigned int m_maxParticles; // Maximum emitter size
	unsigned int m_lastUsedParticleIndex; // Last used particle in the array
	unsigned int m_numLiveParticles; // Current active particles, keeps track if we reached max size
	unsigned int m_partsPerGen; // How many particles spawn per emittion
	float m_timeForGen; // How often the emitter generates new particles
	float m_timeSinceLastParticleGen; // Timer for generating new particles
	std::string m_texturePath;
	glm::vec3 m_emitterPos; // Position of the emitter
	Particle* m_particles; // Array of particles

public:
	ParticleEmitterComponent(const unsigned int maxParticles, const unsigned int partsPerGen, const float timeForGen, std::string textureName)
	{
		m_maxParticles = maxParticles;
		m_partsPerGen = partsPerGen;
		m_timeForGen = timeForGen;
		m_texturePath = textureName;
		m_particles = new Particle[m_maxParticles];
		m_emitterPos = glm::vec3(0.0f);
		m_lastUsedParticleIndex = 0;
		m_numLiveParticles = 0;
		m_timeSinceLastParticleGen = 0.0f;
	}

	void setEmitterPos(const glm::vec3 newPos)
	{
		m_emitterPos = newPos;
	}

	void OnUpdate(float dt) override
	{
		// generate new particles
		m_timeSinceLastParticleGen += dt;

		if (m_timeSinceLastParticleGen > m_timeForGen)
		{
			for (int i = 0; i < m_partsPerGen; i++)
			{
				int particleIndex = findUnusedParticle();
				m_particles[particleIndex].life = 500.0f;
				//float randomXStart = ((rand() % RAND_MAX) / (float)RAND_MAX) * 50000.0f - 25000.0f;
				//float randomZStart = ((rand() % RAND_MAX) / (float)RAND_MAX) * 50000.0f - 25000.0f;
				//m_particles[particleIndex].position = glm::vec3(randomXStart, 5000, randomZStart);
				float randVelX = randomNumRange(20.0f);
				float randVelZ = randomNumRange(20.0f);
				m_particles[particleIndex].position = glm::vec3(m_emitterPos.x, m_emitterPos.y, m_emitterPos.z);
				m_particles[particleIndex].velocity = glm::vec3(randVelX, 30.0f, randVelZ);
				m_particles[particleIndex].colour = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
				m_particles[particleIndex].finalColour = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
				m_particles[particleIndex].size = 100;
			}

			m_timeSinceLastParticleGen = 0;
		}
	}

	void OnMessage(const std::string m) override {}

	void sortParticles()
	{
		// sort the particles based on their distance from the camera
		std::sort(&m_particles[0], &m_particles[m_maxParticles]);
	}

	int findUnusedParticle()
	{
		for (int i = m_lastUsedParticleIndex; i < m_maxParticles; i++) {
			if (m_particles[i].life <= 0) {
				m_lastUsedParticleIndex = i;
				return i;
			}
		}

		for (int i = 0; i < m_lastUsedParticleIndex; i++) {
			if (m_particles[i].life <= 0) {
				m_lastUsedParticleIndex = i;
				return i;
			}
		}

		return 0; // All particles are taken, override the first one
	}

	float randomNumRange(float maxVal)
	{
		return ((rand() % RAND_MAX) / (float)RAND_MAX) * maxVal - (maxVal/2);
	}

	void setPosition(glm::vec3 newPos)
	{
		//m_emitterPos = newPos;
	}

	Particle* getParticles()
	{
		return m_particles;
	}

	unsigned int getMaxParticles()
	{
		return m_maxParticles;
	}

	unsigned int getLiveParticles()
	{
		return m_numLiveParticles;
	}

	std::string getTexture()
	{
		return m_texturePath;
	}
};