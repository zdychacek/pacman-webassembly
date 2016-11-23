#include <sstream>
#include "Game.h"
//#include "GMenu.h"
//#include "Game.h"
//#include "GLevelEditor.h"
//#include "GAbout.h"
//#include "GHighScores.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "InputHandler.h"
#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "MainMenuState.h"
#include "utils.h"

using namespace std;

Game *Game::s_pInstance = nullptr;

Game::Game() : m_pWindow(nullptr),
	       m_pRenderer(nullptr),
				 m_pGameStateMachine(nullptr),
	       m_bRunning(false)
{
}

Game::~Game()
{
  // we must clean up after ourselves to prevent memory leaks
  m_pRenderer = nullptr;
  m_pWindow = nullptr;
}

bool Game::init(string title, int xpos, int ypos, int width, int height, bool fullscreen)
{
  int flags = 0;

  // store the game width and height
  m_gameWidth = width;
  m_gameHeight = height;

  if (fullscreen)
  {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  // attempt to initialise SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
  {
    cerr << "Could not initialize SDL! Error: " << SDL_GetError();

    return false;
  }

  cout << "SDL init success" << endl;

  // init the window
  m_pWindow = SDL_CreateWindow(
      title.c_str(),
      xpos,
      ypos,
      width,
      height,
      flags);

  if (m_pWindow == nullptr)
  {
    cerr << "Could not create window! Error: " << SDL_GetError();

    return false;
  }

  cout << "Window creation success" << endl;

  m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

  if (m_pRenderer == nullptr)
  {
    cerr << "Could not create renderer! Error:" << SDL_GetError();

    return false;
  }

  cout << "Renderer creation success." << endl;

  SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

#ifndef __EMSCRIPTEN__
  SDL_Surface *icon = SDL_LoadBMP("assets/gfx/icon.bmp");
  SDL_SetWindowIcon(m_pWindow, icon);
  SDL_FreeSurface(icon);
#endif
  SDL_ShowCursor(SDL_DISABLE);

  if (TTF_Init() == -1)
  {
    cerr << "Could not initilize SDL_ttf! Error: " << SDL_GetError();

    return false;
  }

  m_fStdFont = TTF_OpenFont("assets/fonts/font.ttf", 17);

  if (m_fStdFont == nullptr)
  {
    cerr << "Could not load font! Error: " << SDL_GetError();

    return false;
  }

  // add some sound effects - TODO move to better place
  TheSoundManager::Instance()->load("assets/sfx/appear.wav", "appear", SOUND_SFX); // SOUND_MUSIC
  TheSoundManager::Instance()->playSound("appear", 0);

	// register the types for the game
  TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());

  // start the menu state
  m_pGameStateMachine = new GameStateMachine();
  m_pGameStateMachine->changeState(new MainMenuState());

	m_curCursor = new Cursor();

  m_bRunning = true; // everything inited successfully, start the main loop

  return true;
}

void Game::render()
{
  SDL_RenderClear(m_pRenderer);

  m_pGameStateMachine->render();

  m_curCursor->draw();

  SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
  int x, y;

  SDL_GetMouseState(&x, &y);

  m_curCursor->setX(x);
  m_curCursor->setY(y);
  m_curCursor->anim();

  m_pGameStateMachine->update();
}

void Game::handleEvents()
{
  TheInputHandler::Instance()->update();
}

void Game::clean()
{
  cout << "Cleaning game" << endl;

  TheInputHandler::Instance()->clean();

  m_pGameStateMachine->clean();

  delete m_pGameStateMachine;
  m_pGameStateMachine = nullptr;

	delete m_curCursor;
	m_curCursor = nullptr;

  TTF_CloseFont(m_fStdFont);

  TheTextureManager::Instance()->clearTextureMap();

  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}

bool Game::isWindowActive()
{
  return !(SDL_GetWindowFlags(m_pWindow) & SDL_WINDOW_MINIMIZED);
}
