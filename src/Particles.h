/*
 * Particles.h
 *
 *  Created on: 1 Jul 2015
 *      Author: eva
 */

#ifndef PARTICLES_H_
#define PARTICLES_H_

#include <iostream>
#include "Screen.h"
using namespace std;

namespace hbt {

struct Particles { // struct is like class but contains are public by default, class has contains private by default
public:
	double m_x;
	double m_y;
	double m_xSpeed;
	double m_ySpeed;
	const static double m_SpeedMod = 0.06;
	double m_Direction;
	double m_rSpeed;
	const static double m_W2H = 1.0*Screen::SCREEN_WIDTH/Screen::SCREEN_HEIGH;
public:
	Particles();
	void update(int elapsed);
	virtual ~Particles();

private:
	void reset();
};

} /* namespace hbt */

#endif /* PARTICLES_H_ */
