#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <SDL2/SDL.h>
#include <time.h>
#include <iostream>
#include "Game.h"

using namespace std;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

Uint32 frameStart, frameTime = 0;
bool isDone = false;

void main_loop(void *)
{
  if (!TheGame::Instance()->isRunning())
  {
#ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
#else
    isDone = true;
#endif

    return;
  }

	if (!TheGame::Instance()->isWindowActive())
	{
	  return;
	}

	frameStart = SDL_GetTicks();

	TheGame::Instance()->handleEvents();
	TheGame::Instance()->update();
	TheGame::Instance()->render();

	frameTime = SDL_GetTicks() - frameStart;

	if (frameTime < DELAY_TIME)
	{
		SDL_Delay(static_cast<int>(DELAY_TIME - frameTime));
	}
}

#ifdef __EMSCRIPTEN__
extern "C" int mainf(int argc, char *argv[])
{
#else
int main(int argc, char *argv[])
{
#endif
  srand((unsigned)time(nullptr));

  cout << "App init attempt..." << endl;

  if (TheGame::Instance()->init("The game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, false))
  {
    cout << "App init success!" << endl;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(main_loop, nullptr, -1, 1);
#else
    while (!isDone)
    {
      main_loop(nullptr);
    }
#endif
  }
  else
  {
    cout << "App init failure: " << SDL_GetError() << endl;

    return -1;
  }

  cout << "App closing..." << endl;
  TheGame::Instance()->clean();

  return 0;
}
