#ifndef __Game__
#define __Game__

#include <SDL2/SDL.h>
#include "GameStateMachine.h"
#include "Cursor.h"
//#include "GTopList.h"

class Game
{
public:
  static Game *Instance()
  {
    if (s_pInstance == nullptr)
    {
      s_pInstance = new Game;

      return s_pInstance;
    }

    return s_pInstance;
  }
  bool init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen);
  void render();
  void update();
  void handleEvents();
  void clean();
  void quit() { m_bRunning = false; }

  SDL_Renderer *getRenderer() const { return m_pRenderer; }
  SDL_Window *getWindow() const { return m_pWindow; }
  GameStateMachine *getStateMachine() { return m_pGameStateMachine; }
  bool isRunning() { return m_bRunning; }
  int getGameWidth() const { return m_gameWidth; }
  int getGameHeight() const { return m_gameHeight; }
  TTF_Font *getStdFont() const { return m_fStdFont; }
  bool isWindowActive();

private:
  static Game *s_pInstance;

  SDL_Window *m_pWindow;
  SDL_Renderer *m_pRenderer;
  GameStateMachine *m_pGameStateMachine;
  TTF_Font *m_fStdFont;
  Cursor *m_curCursor;

  bool m_bRunning;
  int m_gameWidth;
  int m_gameHeight;

  Game();
  ~Game();
  Game(const Game &);
  Game &operator=(const Game &);
};

typedef Game TheGame;

#endif
