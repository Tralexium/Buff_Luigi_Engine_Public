#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

struct Particle
{
	// initialised to dead particle (-1.0f life)
	Particle() : life(1.0f), size(1.0f), colour(1.0f, 0.0f, 0.0f, 1.0f), velocity(0.0f, 0.0f, 0.0f) {}

	// variables that need passing to the shader
	float life, size, cameraSqDistance;
	glm::vec3 position, velocity;
	glm::vec4 colour;

	// sort to ensure the particles further away are drawn first
	bool operator<(const Particle& that) const
	{
		return this->cameraSqDistance > that.cameraSqDistance;
	}
};

class ParticleEmitterComponent : public Component
{
private:
	unsigned int m_maxParticles;
	unsigned int m_particleRenderer;
	unsigned int m_lastUsedParticleIndex;
	unsigned int m_numLiveParticles;
	float m_timeSinceLastParticleGen;
	Particle* m_particles;

public:
	ParticleEmitterComponent
	(const unsigned int maxParticles = 10000) : m_particleRenderer(maxParticles), m_maxParticles(maxParticles)
	{
		m_particles = new Particle[m_maxParticles];
		m_lastUsedParticleIndex = 0;
		m_numLiveParticles = 0;
		m_timeSinceLastParticleGen = 0;
	}

	void OnUpdate(float dt) override 
	{
		// generate new particles
		m_timeSinceLastParticleGen += dt;

		if (m_timeSinceLastParticleGen > 1)
		{
			int particleIndex = findUnusedParticle();
			m_particles[particleIndex].life = 500.0f;
			float randomXStart = ((rand() % RAND_MAX) / (float)RAND_MAX) * 50000.0f - 25000.0f;
			float randomZStart = ((rand() % RAND_MAX) / (float)RAND_MAX) * 50000.0f - 25000.0f;
			m_particles[particleIndex].position = glm::vec3(randomXStart, 5000, randomZStart);
			m_particles[particleIndex].velocity = glm::vec3(10, -100, 10);
			m_particles[particleIndex].colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			m_particles[particleIndex].size = 100;

			m_timeSinceLastParticleGen = 0;
		}
	}

	void OnMessage(const std::string m) override {}

	void sortParticles()
	{
		// sort the particles based on their distance from the camera
		std::sort(&m_particles[0], &m_particles[m_maxParticles], Particle::operator<);
	}

	int findUnusedParticle() 
	{
		for (int i = m_lastUsedParticleIndex; i < m_maxParticles; i++) {
			if (m_particles[i].life < 0) {
				m_lastUsedParticleIndex = i;
				return i;
			}
		}

		for (int i = 0; i < m_lastUsedParticleIndex; i++) {
			if (m_particles[i].life < 0) {
				m_lastUsedParticleIndex = i;
				return i;
			}
		}

		return 0; // All particles are taken, override the first one
	}
};