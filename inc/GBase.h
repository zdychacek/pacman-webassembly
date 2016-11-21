#ifndef GBASE_H
#define GBASE_H

#include "utils.h"
#include "MControlBase.h"

class GGame;

class GBase
{
public:
  GBase();
  virtual ~GBase();
  virtual void keyUp(Uint8 key);
  virtual void keyDown(Uint8 key);
  virtual void mouseMove(int x, int y);
  virtual void mouseLButtonDown(int x, int y);
  virtual void mouseLButtonUp(int x, int y);
  virtual void mouseRButtonDown(int x, int y);
  virtual void mouseRButtonUp(int x, int y);
  virtual void render(SDL_Surface *screen);
  virtual void move();
  inline GGame *getRun() const { return m_pRun; }
  inline MControlBase *getFocusCtrl() const { return m_pFocusCtrl; }
  inline void setFocusCtrl(MControlBase *ctrl) { m_pFocusCtrl = ctrl; }
protected:
  GGame *m_pRun;
  MControlBase *m_pFocusCtrl;
};

#endif
