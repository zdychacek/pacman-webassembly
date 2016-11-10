#include <sstream>
#include <stdio.h>
#include <stdlib.h>
//#include <io.h>
#include <fcntl.h>	// pro pøíznaky otvírání souborù
#include "GRun.h"
//#include "GMenu.h"
//#include "GGame.h"
//#include "GLevelEditor.h"
//#include "GAbout.h"
//#include "GHighScores.h"
#include "TextureManager.h"
#include "utils.h"

GRun* GRun::s_pInstance = nullptr;

GRun::GRun(int w, int h, int bpp, bool fullscreen):
	m_bWantFPS(true),
	m_fFPS(1.0f),
	m_pActual(nullptr)
{
	setFocus(nullptr);
}

GRun::GRun():
	m_pActual(nullptr)
{
	/*m_nResX = 504;
	m_nResY = 420;
	m_nBpp = 32;
	m_bFullscreen = false;
	saveIni();*/

	loadIni();	// naète inifile

	/*m_mTopList = new GTopList();
	m_mTopList->loadList();*/
}

GRun::~GRun()
{
	saveIni();
	//m_mTopList->saveList();

	/*if(m_mTopList != nullptr) {
		delete m_mTopList;
		m_mTopList = nullptr;
	}*/

	if (m_curCursor != nullptr) {
		delete m_curCursor;
		m_curCursor = nullptr;
	}

	TheTextureManager::Instance()->clearTextureMap();

	TTF_CloseFont(m_fStdFont);

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void GRun::keyDown(Uint8 key) {
	if (getFocus() != nullptr) m_pActual->keyDown(key);
}

void GRun::keyUp(Uint8 key) {
	if (getFocus() != nullptr) m_pActual->keyUp(key);
}

void GRun::move(int ms) {
	m_fFPS = 1000.0f / ms;

	/*if (getFocus() != nullptr) m_pActual->move();

	if (isCursorShow()) {
		int x, y;
		SDL_GetMouseState(&x, &y);

		m_curCursor->setX(x);
		m_curCursor->setY(y);
		m_curCursor->anim();
	}*/
}

void GRun::render() {
	//if (getFocus() != nullptr) {


		SDL_RenderClear(m_pRenderer);

		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(m_pRenderer, nullptr);

		drawText(getStdFont(), SDL_Color { 200, 0, 0, 0 }, "huhu", 3, 3);

		SDL_RenderPresent(m_pRenderer);

		/*SDL_FillRect(getScreen(), nullptr, 0x0);
		m_pActual->render(getScreen());

		// vypsání FPS
		if(m_bWantFPS) {
			char str[15];

			sprintf(str, "FPS: %d", (int)m_fFPS);
			drawText(getStdFont(), color, str, 3, 3, getScreen());
		}

		if(isCursorShow()) m_curCursor->draw(getScreen());

		SDL_UpdateWindowSurface(m_pWindow);*/
	//}
}

bool GRun::init(const char* title, int xPos, int yPos, int w, int h, bool fullscreen) {
	m_nResX = w;
	m_nResY = h;
	m_bFullscreen = fullscreen;

	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
		std::cerr << "Could not initialize SDL! Error:" << SDL_GetError();

		return false;
	}

	int windowFlags = SDL_WINDOW_SHOWN;

	if (m_bFullscreen) {
		windowFlags |= SDL_WINDOW_FULLSCREEN;
	}

	m_pWindow = SDL_CreateWindow(
		title,
		xPos,
		yPos,
		m_nResX,
		m_nResY,
		windowFlags
	);

	if (m_pWindow == nullptr) {
		std::cerr << "Could not create window! Error:" << SDL_GetError();

		return false;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

	if (m_pRenderer == nullptr) {
		std::cerr << "Could not create renderer! Error:" << SDL_GetError();

		return false;
	}

	SDL_Surface* icon = SDL_LoadBMP("assets/gfx/icon.bmp");
	SDL_SetWindowIcon(m_pWindow, icon);
	SDL_FreeSurface(icon);

	SDL_ShowCursor(SDL_DISABLE);

	// TODO: http://stackoverflow.com/questions/22156815/how-to-disable-key-repeat-in-sdl2
	//SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	// vytvoreni kurzoru
	//m_curCursor = new GCursor;
	setCursor(true);

	if (TTF_Init() == -1) {
		std::cerr << "Could not initilize SDL_ttf! Error:" << SDL_GetError();

		return false;
	}

	m_fStdFont = TTF_OpenFont("assets/fonts/font.ttf", 17);

	if (m_fStdFont == nullptr) {
		std::cerr << "Could not load font! Error:" << SDL_GetError();
		exitProgram();
	}

	#ifndef __EMSCRIPTEN__
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
			std::cerr << "Could not initilize SDL_mixer! Error:" << SDL_GetError();

			m_bSounds = false;
		}
	#endif

	m_bRunning = true;

	return true;
}

void GRun::exitProgram() {
	//fade(getScreen(), nullptr, 2, 0);

	if(m_pActual != nullptr) delete m_pActual;

	m_pActual = nullptr;
	m_bRunning = false;
}

void GRun::startGame() {
	if(m_pActual != nullptr) delete m_pActual;

	//m_pActual = new GGame(this);
	fprintf(stderr, "Starting game...\n");
}

void GRun::startMenu() {
	if(m_pActual != nullptr) delete m_pActual;

	//m_pActual = new GMenu(this);
	fprintf(stderr, "Starting menu...\n");
}

void GRun::startAbout() {
	if(m_pActual != nullptr) delete m_pActual;

	//m_pActual = new GAbout(this);
	fprintf(stderr, "Starting about...\n");
}

void GRun::startHighScores(bool add, int score) {
	if(m_pActual != nullptr) delete m_pActual;

	//m_pActual = new GHighScores(this, add, score);
	fprintf(stderr, "Starting high scores...\n");
}

void GRun::startLevelEditor() {
	if(m_pActual != nullptr) delete m_pActual;

	//m_pActual = new GLevelEditor(this);
	fprintf(stderr, "Starting level editor...\n");
}

void GRun::mouseLButtonDown(int x,int y) {
	if(getFocus() != nullptr) m_pActual->mouseLButtonDown(x, y);
}

void GRun::mouseRButtonDown(int x,int y) {
	if(getFocus() != nullptr) m_pActual->mouseRButtonDown(x, y);
}

void GRun::mouseLButtonUp(int x,int y) {
	if(getFocus() != nullptr) m_pActual->mouseLButtonUp(x, y);
}

void GRun::mouseRButtonUp(int x,int y) {
	if(getFocus() != nullptr) m_pActual->mouseRButtonUp(x, y);
}

void GRun::mouseMove(int x,int y) {
	if(getFocus() != nullptr) m_pActual->mouseMove(x, y);
}

bool GRun::saveIni() {
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

bool GRun::loadIni() {
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

bool GRun::processEvents() {
	SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
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

void GRun::setFocus(GBase *base) {
	if(base != nullptr) m_pActual = base;
}

bool GRun::isWindowActive () {
	return !(SDL_GetWindowFlags(m_pWindow) & SDL_WINDOW_MINIMIZED);
}
