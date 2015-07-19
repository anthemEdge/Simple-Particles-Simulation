/*
 * Swarm.h
 *
 *  Created on: 1 Jul 2015
 *      Author: eva
 */

#ifndef SWARM_H_
#define SWARM_H_

#include "Particles.h"

namespace hbt {

class Swarm {
public:
	const static int NPARTICLES = 9000;
private:
	Particles *m_pParticles;
	int lastRun;
public:
	Swarm();
	void update(int ticks);
	virtual ~Swarm();
	const Particles * const getParticles() {
		return m_pParticles;
	}
	;
};

} /* namespace hbt */

#endif /* SWARM_H_ */
