/*
 * Particles.cpp
 *
 *  Created on: 1 Jul 2015
 *      Author: eva
 */

#include <stdlib.h>
#include <math.h>
#include "Particles.h"

namespace hbt {

Particles::Particles() :
		m_x(0), m_y(0) {

	// Random initial conditions

	// 0.05 * rand() / RAND_MAX

//	m_x = 2.0 * rand() / RAND_MAX - 1; // rand() / RAND_MAX value from 0 to 1
//	m_y = 2.0 * rand() / RAND_MAX - 1; // this gives value from -1 to 1

	m_Direction = 2.0 * M_PI * (double) rand() / RAND_MAX;
	m_rSpeed = m_SpeedMod * ((double) rand() / RAND_MAX - 0.5);

	m_rSpeed *= m_rSpeed;
}

void Particles::update(int elapsed) {

	m_Direction += elapsed * 0.0001;

	m_xSpeed = m_rSpeed * cos(m_Direction);
	m_ySpeed = m_rSpeed * sin(m_Direction);

	m_x += m_xSpeed * elapsed * 0.1;
	m_y += m_ySpeed * elapsed * 0.1;

	if (m_x < -m_W2H || m_x >= m_W2H) {
		reset();
	}

	if (m_y < -1.0 || m_y >= 1.0) {
		reset();
	}

}

void Particles::reset() {
	m_x = 0;
	m_y = 0;
	m_Direction = 2.0 * M_PI * (double) rand() / RAND_MAX;
	m_rSpeed = m_SpeedMod * ((double) rand() / RAND_MAX - 0.5);
	m_rSpeed *= m_rSpeed;
}

Particles::~Particles() {
}

} /* namespace hbt */
