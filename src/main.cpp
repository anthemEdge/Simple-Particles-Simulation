//============================================================================
// Name        : SDL.cpp
// Author      : AnthemEdge
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "Screen.h"
#include "Swarm.h"

using namespace std;
using namespace hbt;

int main() {

	srand(time(NULL)); // random number generator from using time as seed

	Screen screen;

	if (screen.init() != true) {
		cout << "Error in Screen Initialisation." << endl;
	}

	// Swarm
	Swarm swarm;
	const Particles * const pParticles = swarm.getParticles();

	Uint8 red = 0;
	Uint8 green = 0;
	Uint8 blue = 0;

	int ticks;
	double sinRed;
	double sinGreen;
	double sinBlue;

	Particles particle;
	int x;
	int y;

	while (screen.processEvent()) {


		// colour ticking
		ticks = SDL_GetTicks(); // ticks in ms
		sinRed = sin((double) ticks / 3000) + 1; // 2 seconds period
		sinGreen = cos((double) ticks / 1750) + 1; // 1.5 seconds period
		sinBlue = sin((double) ticks / 2500) + 1; // 2.5 seconds period
		red = (Uint8) (sinRed * 127.5);
		green = (Uint8) (sinGreen * 127.5);
		blue = (Uint8) (sinBlue * 127.5);

		// Draw Blur
		screen.boxBlur();

		// Set Swarm to buffer
		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			particle = pParticles[i];
			x = (int) ((particle.m_x + particle.m_W2H)
					* (screen.SCREEN_WIDTH / (2 * particle.m_W2H)));
			y = (int) ((particle.m_y + 1) * (screen.SCREEN_HEIGH / 2));
			screen.setPixel(x, y, red, green, blue);
		}



		// Update Particle
		// Draw particle
		// Check for messages/events

		// Update the position of the swarm based on time
		swarm.update(ticks);

		// Draw what ever is un buffer
		screen.update();
	}

	screen.close();
	return 0;
}
