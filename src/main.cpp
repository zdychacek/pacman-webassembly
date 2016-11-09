#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>

#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
#endif

#include "test.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#ifdef __EMSCRIPTEN__
extern "C" int mainf (int argc, char *argv[]) {
#else
int main (int argc, char *argv[]) {
#endif
	// The window we'll be rendering to
	SDL_Window* window = NULL;

	// The surface contained by the window
	SDL_Surface* window_surface = NULL;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! Error: %s\n", SDL_GetError());
		return -1;
	}

	window = SDL_CreateWindow(
		"SDL2 App",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (window == NULL) {
		printf("Could not create window! Error: %s\n", SDL_GetError());
		return -1;
	}

	// Fetch the window's SDL_Surface
	window_surface = SDL_GetWindowSurface(window);

	// Fill in the window's surface
	SDL_FillRect(
		window_surface,
		NULL,
		SDL_MapRGB(window_surface->format, 0xff, 0x0, 0x0)
	);

	// Flip the window surface
	SDL_UpdateWindowSurface(window);

	// Wait 4 seconds before continuing
	#ifndef __EMSCRIPTEN__
		SDL_Delay(4000);
	#endif

	SDL_DestroyWindow(window);

	// Shutdown SDL
	SDL_Quit();

	return 0;
}

/*#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(loop_handler, &ctx, -1, 1);
#else
	while (1)
	{
		loop_handler(&ctx);
	}
#endif*/
