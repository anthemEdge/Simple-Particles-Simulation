/*
 * Screen.h
 *
 *  Created on: 29 Jun 2015
 *      Author: eva
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <iostream>
#include <SDL.h>

using namespace std;
namespace hbt {

class Screen {
private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_buffer1;
	Uint32 *m_buffer2;

public:
	const static int SCREEN_WIDTH = 1000;
	const static int SCREEN_HEIGH = 900;
public:
	Screen();
	bool init(); // false if fails
	void update();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	bool processEvent();
	void close();
	void clear();
	void boxBlur();
	virtual ~Screen();
};

} /* namespace hbt */

#endif /* SCREEN_H_ */
