/*
 * Swarm.cpp
 *
 *  Created on: 1 Jul 2015
 *      Author: eva
 */

#include "Swarm.h"

namespace hbt {

Swarm::Swarm() :
		lastRun(0) {
	m_pParticles = new Particles[NPARTICLES];
}

Swarm::~Swarm() {
	delete[] m_pParticles;
}

void Swarm::update(int ticks) {
	int elapsed = ticks - lastRun;
	lastRun = ticks;
	for (int i = 0; i < NPARTICLES; i++) {
		m_pParticles[i].update(elapsed);
	}
	lastRun = ticks;

}

}
/* namespace hbt */
