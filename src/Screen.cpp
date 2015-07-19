/*
 * Screen.cpp
 *
 *  Created on: 29 Jun 2015
 *      Author: eva
 */

#include <iomanip>
#include "Screen.h"

namespace hbt {

Screen::Screen() :
		m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(
		NULL) {
}

bool Screen::init() {
	// false if fails

	// SDL_Init
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}

	// Window
	m_window = SDL_CreateWindow("Particle Simulation",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
			SCREEN_HEIGH, SDL_WINDOW_SHOWN);
	if (m_window == NULL) {
		Screen::close();
		return false;
	}

	// Renderer
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	// VSYNC to prevent shearing
	if (m_renderer == NULL) {
		Screen::close();
		return false;
	}

	// Texture
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGH);
	if (m_texture == NULL) {
		Screen::close();
		return false;
	}

	// Buffer
	m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGH];
	m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGH];

	if (m_buffer1 == NULL or m_buffer2 == NULL) {
		Screen::close();
		return false;
	}

	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGH * sizeof(Uint32));
	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGH * sizeof(Uint32));
	// 0  is black
	// Writing 255 to a block of memory, hence white
	// 255 is also 0xff, where 0x is a prefix
//
//	for (int i = 0; i < SCREEN_HEIGH * SCREEN_WIDTH; i++) {
//		m_buffer[i] = 0x123456FF;
//	}

	return true;
}

void Screen::update() {

	// Temp operation
	SDL_UpdateTexture(m_texture, NULL, m_buffer1,
			SCREEN_WIDTH * sizeof(Uint32));
	// Draw Texture
	SDL_RenderClear(m_renderer);
	// Empty Renderer
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	// copy texture to the texture
	SDL_RenderPresent(m_renderer);
	// Present Render

}

void Screen::boxBlur() {
	// Swap the buffers, so pixel is in m_buffer2 and we are drawing into m_buffer1

	// Coping buffer 2 from buffer but keep buffer1 at the same time
	Uint32 *temp = m_buffer1;
	m_buffer1 = m_buffer2;
	m_buffer2 = temp;

	for (int x = 0; x < SCREEN_WIDTH; x++) {
		for (int y = 0; y < SCREEN_HEIGH; y++) {

			int redSum = 0;
			int greenSum = 0;
			int blueSum = 0;
			for (int row = -1; row <= 1; row++) {
				for (int col = -1; col <= 1; col++) {
					int currentX = x + col;
					int currentY = y + row;
					if (currentX >= 0 && currentY >= 0
							&& currentX < SCREEN_WIDTH
							&& currentY < SCREEN_HEIGH) {
						Uint32 colour = m_buffer2[SCREEN_WIDTH * currentY
								+ currentX];

//						Uint8 red = (colour & 0xFF000000) >> 24;
//						Uint8 green = (colour & 0x00FF0000) >> 16;
//						Uint8 blue = (colour & 0x0000FF00) >> 8;

						Uint8 red = colour >> 24;
						Uint8 green = colour >> 16;
						Uint8 blue = colour >> 8;

						redSum += red;
						greenSum += green;
						blueSum += blue;
					}
				}
			}

			Uint8 red = redSum / 9;
			Uint8 green = greenSum / 9;
			Uint8 blue = blueSum / 9;

			setPixel(x, y, red, green, blue);
		}
	}
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

	if (x < 0 or x >= SCREEN_WIDTH or y < 0 or y >= SCREEN_HEIGH) {
		return;
	}

	Uint32 colour = 0;
	colour += red;
	colour <<= 8;
	colour += green;
	colour <<= 8;
	colour += blue;
	colour <<= 8;
	colour += 0xFF;

	m_buffer1[(y * SCREEN_WIDTH) + x] = colour;

}

bool Screen::processEvent() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
}

void Screen::close() {
	if (m_buffer2 != NULL) {
		delete[] m_buffer2;
	}
	if (m_buffer1 != NULL) {
		delete[] m_buffer1;
	}
	if (m_texture != NULL) {
		SDL_DestroyTexture(m_texture);
	}
	if (m_renderer != NULL) {
		SDL_DestroyRenderer(m_renderer);
	}
	if (m_window != NULL) {
		SDL_DestroyWindow(m_window);
	}
	SDL_Quit();
}

Screen::~Screen() {
// TODO Auto-generated destructor stub
}

}
/* namespace hbt */
