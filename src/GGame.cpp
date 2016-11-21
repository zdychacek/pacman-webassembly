#include <sstream>
#include <stdlib.h>
//#include <io.h>
#include <fcntl.h> // pro pøíznaky otvírání souborù
#include "GGame.h"
//#include "GMenu.h"
//#include "GGame.h"
//#include "GLevelEditor.h"
//#include "GAbout.h"
//#include "GHighScores.h"
#include "TextureManager.h"
#include "utils.h"

using namespace std;

GGame *GGame::s_pInstance = nullptr;

GGame::GGame(int w, int h, int bpp, bool fullscreen) : m_pActual(nullptr)
{
  setFocus(nullptr);
}

GGame::GGame() : m_pActual(nullptr)
{
  /*m_nResX = 504;
	m_nResY = 420;
	m_nBpp = 32;
	m_bFullscreen = false;
	saveIni();*/

  loadIni();

  /*m_mTopList = new GTopList();
	m_mTopList->loadList();*/
}

GGame::~GGame()
{
  saveIni();
  //m_mTopList->saveList();

  /*if(m_mTopList != nullptr) {
		delete m_mTopList;
		m_mTopList = nullptr;
	}*/

  if (m_curCursor != nullptr)
  {
    delete m_curCursor;
    m_curCursor = nullptr;
  }

  TheTextureManager::Instance()->clearTextureMap();

  TTF_CloseFont(m_fStdFont);

  SDL_DestroyRenderer(m_pRenderer);
  SDL_DestroyWindow(m_pWindow);
  SDL_Quit();
}

void GGame::keyDown(Uint8 key)
{
  if (getFocus() != nullptr)
    m_pActual->keyDown(key);
}

void GGame::keyUp(Uint8 key)
{
  if (getFocus() != nullptr)
    m_pActual->keyUp(key);
}

void GGame::move(int ms)
{
  //if (getFocus() != nullptr) m_pActual->move();

  if (isCursorShow())
  {
    int x, y;

    SDL_GetMouseState(&x, &y);

    m_curCursor->setX(x);
    m_curCursor->setY(y);
    m_curCursor->anim();
  }
}

void GGame::render()
{
  //if (getFocus() != nullptr) {
  SDL_RenderClear(m_pRenderer);

  SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(m_pRenderer, nullptr);

  drawText(getStdFont(), SDL_Color{200, 0, 0, 0}, "Hello World!", 3, 3);

  if (isCursorShow())
  {
    m_curCursor->draw();
  }

  SDL_RenderPresent(m_pRenderer);
  //}
}

bool GGame::init(const char *title, int xPos, int yPos, int w, int h, bool fullscreen)
{
  m_nResX = w;
  m_nResY = h;
  m_bFullscreen = fullscreen;

  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
  {
    cerr << "Could not initialize SDL! Error:" << SDL_GetError();

    return false;
  }

  int windowFlags = SDL_WINDOW_SHOWN;

  if (m_bFullscreen)
  {
    windowFlags |= SDL_WINDOW_FULLSCREEN;
  }

  m_pWindow = SDL_CreateWindow(
      title,
      xPos,
      yPos,
      m_nResX,
      m_nResY,
      windowFlags);

  if (m_pWindow == nullptr)
  {
    cerr << "Could not create window! Error:" << SDL_GetError();

    return false;
  }

  m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

  if (m_pRenderer == nullptr)
  {
    cerr << "Could not create renderer! Error:" << SDL_GetError();

    return false;
  }

#ifndef __EMSCRIPTEN__
  SDL_Surface *icon = SDL_LoadBMP("assets/gfx/icon.bmp");
  SDL_SetWindowIcon(m_pWindow, icon);
  SDL_FreeSurface(icon);
#endif

  SDL_ShowCursor(SDL_DISABLE);

  // TODO: http://stackoverflow.com/questions/22156815/how-to-disable-key-repeat-in-sdl2
  //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

  // vytvoreni kurzoru
  m_curCursor = new GCursor();
  setCursor(true);

  if (TTF_Init() == -1)
  {
    cerr << "Could not initilize SDL_ttf! Error:" << SDL_GetError();

    return false;
  }

  m_fStdFont = TTF_OpenFont("assets/fonts/font.ttf", 17);

  if (m_fStdFont == nullptr)
  {
    cerr << "Could not load font! Error:" << SDL_GetError();
    quit();
  }

  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
  {
    cerr << "Could not initilize SDL_mixer! Error:" << SDL_GetError();

    m_bSounds = false;
  }

  m_bRunning = true;

  Mix_PlayChannel(-1, Mix_LoadWAV("assets/sfx/appear.wav"), 0);

  return true;
}

void GGame::quit()
{
  if (m_pActual != nullptr)
  {
    delete m_pActual;
  }

  m_pActual = nullptr;
  m_bRunning = false;
}

void GGame::startGame()
{
  if (m_pActual != nullptr)
  {
    delete m_pActual;
  }

  //m_pActual = new GGame(this);
  cout << "Starting game..." << endl;
}

void GGame::startMenu()
{
  if (m_pActual != nullptr)
  {
    delete m_pActual;
  }

  //m_pActual = new GMenu(this);
  cout << "Starting menu..." << endl;
}

void GGame::startAbout()
{
  if (m_pActual != nullptr)
  {
    delete m_pActual;
  }

  //m_pActual = new GAbout(this);
  cout << "Starting about..." << endl;
}

void GGame::startHighScores(bool add, int score)
{
  if (m_pActual != nullptr)
  {
    delete m_pActual;
  }

  //m_pActual = new GHighScores(this, add, score);
  cout << "Starting high scores..." << endl;
}

void GGame::startLevelEditor()
{
  if (m_pActual != nullptr)
  {
    delete m_pActual;
  }

  //m_pActual = new GLevelEditor(this);
  cout << "Starting level editor..." << endl;
}

void GGame::mouseLButtonDown(int x, int y)
{
  if (getFocus() != nullptr)
  {
    m_pActual->mouseLButtonDown(x, y);
  }
}

void GGame::mouseRButtonDown(int x, int y)
{
  if (getFocus() != nullptr)
  {
    m_pActual->mouseRButtonDown(x, y);
  }
}

void GGame::mouseLButtonUp(int x, int y)
{
  if (getFocus() != nullptr)
  {
    m_pActual->mouseLButtonUp(x, y);
  }
}

void GGame::mouseRButtonUp(int x, int y)
{
  if (getFocus() != nullptr)
  {
    m_pActual->mouseRButtonUp(x, y);
  }
}

void GGame::mouseMove(int x, int y)
{
  if (getFocus() != nullptr)
  {
    m_pActual->mouseMove(x, y);
  }
}

bool GGame::saveIni()
{
  FILE *infile;

  m_ini.resX = m_nResX;
  m_ini.resY = m_nResY;
  m_ini.bpp = m_nBpp;
  m_ini.fs = m_bFullscreen;
  m_ini.effects = m_bEffects;
  m_ini.sounds = m_bSounds;

  /*if((infile = fopen(_INIFILE, "rw")) == -1) {
		fprintf(stderr, "Soubor %s neexistuje!\n", _INIFILE);
		return false;
	}

	fwrite(infile, &m_ini, sizeof(m_ini));
	fclose(infile);*/

  return true;
}

bool GGame::loadIni()
{
  /*FILE *infile;

	if((infile = fopen(_INIFILE, "r")) == -1) {
		fprintf(stderr, "Soubor %s neexistuje!\n", _INIFILE);
		return false;
	}

	fread(infile, &m_ini, sizeof(m_ini));
	fclose(infile);*/

  m_nResX = 504;
  m_nResY = 420;
  m_nBpp = 32;
  m_bEffects = true;
  m_bSounds = true;
  m_bFullscreen = false;

  //fprintf(stderr, "resX: %d resY: %d bpp: %d effects %d sounds %d fs %d\n",
  //	ini.resX, ini.resY, ini.bpp, ini.effects, ini.sounds, ini.fs);

  return true;
}

bool GGame::processEvents()
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      m_bRunning = false;
    }
  }

  return true;

  /*SDL_Event event;

	while(SDL_PollEvent(&event)) {
		switch(event.type) {
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			keyDown(event.key.keysym.sym);

			break;
		case SDL_KEYUP:
			keyUp(event.key.keysym.sym);

			break;
		case SDL_MOUSEMOTION:
			mouseMove(event.motion.x, event.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch(event.button.button) {
			case SDL_BUTTON_LEFT:
				mouseLButtonDown(event.button.x, event.button.y);
				break;
			case SDL_BUTTON_RIGHT:
				mouseRButtonDown(event.button.x, event.button.y);
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch(event.button.button) {
			case SDL_BUTTON_LEFT:
				mouseLButtonUp(event.button.x, event.button.y);
				break;
			case SDL_BUTTON_RIGHT:
				mouseRButtonUp(event.button.x, event.button.y);
				break;
			}
			break;
		}
	}

	return true;*/
}

void GGame::setFocus(GBase *base)
{
  if (base != nullptr)
  {
    m_pActual = base;
  };
}

bool GGame::isWindowActive()
{
  return !(SDL_GetWindowFlags(m_pWindow) & SDL_WINDOW_MINIMIZED);
}
