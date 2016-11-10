#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "GRun.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

Uint32 frameStart, frameTime = 0;
bool isDone = false;

void main_loop (void* ctx) {
	if (!TheGRun::Instance()->isRunning()) {
		#ifdef __EMSCRIPTEN__
			emscripten_cancel_main_loop();
		#else
			isDone = true;
		#endif

		return;
	}

	frameStart = SDL_GetTicks();

	if (TheGRun::Instance()->isWindowActive()) {
		TheGRun::Instance()->processEvents();
		TheGRun::Instance()->move(frameTime);
		TheGRun::Instance()->render();
	}

	frameTime = SDL_GetTicks() - frameStart;

	if (frameTime < DELAY_TIME) {
		SDL_Delay((int)(DELAY_TIME - frameTime));
	}
}

#ifdef __EMSCRIPTEN__
extern "C" int mainf (int argc, char *argv[]) {
#else
int main (int argc, char *argv[]) {
#endif
	srand((unsigned)time(nullptr));

	std::cout << "game init attempt...\n";

	if (TheGRun::Instance()->init("The game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, false)) {
		std::cout << "game init success!\n";

		#ifdef __EMSCRIPTEN__
			emscripten_set_main_loop_arg(main_loop, nullptr, -1, 1);
		#else
			while (!isDone) {
				main_loop(nullptr);
			}
		#endif
	}

	return 0;
}
