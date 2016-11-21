#ifndef GGAME_H
#define GGAME_H

#include <SDL2/SDL.h>
#include <SDL/SDL_mixer.h>
#ifdef __EMSCRIPTEN__
#include <SDL/SDL_mixer.h>
#else
#include <SDL2/SDL_mixer.h>
#endif
#include "GBase.h"
#include "GCursor.h"
//#include "GTopList.h"

class GGame : public GBase
{
public:
  static GGame *Instance()
  {
    if (s_pInstance == 0)
    {
      s_pInstance = new GGame;

      return s_pInstance;
    }

    return s_pInstance;
  }
  bool init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
  void keyUp(Uint8 key);
  void keyDown(Uint8 key);
  void mouseLButtonDown(int x, int y);
  void mouseLButtonUp(int x, int y);
  void mouseRButtonDown(int x, int y);
  void mouseRButtonUp(int x, int y);
  void mouseMove(int x, int y);
  void render();
  void move(int milisec);
  void startMenu();
  void startGame();
  void quit();
  void startLevelEditor();
  void startAbout();
  void startHighScores(bool add = false, int score = 0);
  void setFocus(GBase *base);
  bool saveIni();
  bool loadIni();
  bool createScreen(int w, int h, int bpp, bool fullscreen = false);
  bool processEvents();
  bool isRunning() { return m_bRunning; }
  inline float getFPS() const { return m_fFPS; }
  inline SDL_Renderer *getRenderer() const { return m_pRenderer; }
  inline GBase *getFocus() { return m_pActual; }
  inline void setCursor(bool yes) { m_bWantCursor = yes; }
  inline bool isCursorShow() const { return m_bWantCursor; }
  bool isWindowActive();
  //inline GTopList* getTopList()const {return m_mTopList;}
  TTF_Font *getStdFont() const { return m_fStdFont; }
  int m_nResX,
      m_nResY,
      m_nBpp;

private:
  static GGame *s_pInstance;

  GGame(int w, int h, int bpp, bool fullscreen);
  GGame();
  GGame(const GGame &);
  GGame &operator=(const GGame &);
  virtual ~GGame();

  bool m_bWantCursor;
  bool m_bWantFPS;
  bool m_bRunning;
  bool m_bEffects;
  bool m_bSounds;
  bool m_bFullscreen;
  float m_fFPS;
  GBase *m_pActual;
  //GTopList *m_mTopList;
  GCursor *m_curCursor;
  TTF_Font *m_fStdFont;
  inifile m_ini;
  SDL_Window *m_pWindow;
  SDL_Renderer *m_pRenderer;
};

typedef GGame TheGGame;

#endif
