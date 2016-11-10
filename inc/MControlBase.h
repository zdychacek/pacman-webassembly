#ifndef MCONTROLBASE_H
#define MCONTROLBASE_H

#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>
#include "utils.h"

class GBase;

class MControlBase
{
public:
	MControlBase(GBase *parent);
	MControlBase():
		m_pParent(NULL),
		m_bVisible(true)
	{}
	virtual ~MControlBase();
	virtual void move(int cx, int cy);
	virtual void draw(SDL_Surface *screen);
	virtual void keyUp(Uint8 key);
	virtual void keyDown(Uint8 key);
	virtual bool mouseLButtonDown(int x, int y);
	virtual bool mouseLButtonUp(int x, int y);
	virtual bool mouseRButtonDown(int x, int y);
	virtual bool mouseRButtonUp(int x, int y);
	virtual bool mouseMove(int x, int y);
	virtual void setX(int x) {m_rectPoz.x = x;}
	virtual int getX()const {return m_rectPoz.x;}
	virtual void setY(int y) {m_rectPoz.y = y;}
	virtual int getY()const {return m_rectPoz.y;}
	inline void setState(int state) {m_nState = state;}
	inline void setVisible(bool yes) {m_bVisible = yes;}
	inline int getState()const {return m_nState;}
	inline bool getVisible()const {return m_bVisible;}
	inline GBase* getParent()const {return m_pParent;}
protected:
	bool isInRect(int x, int y)const;

	bool m_bVisible;
	int m_nState;			// stav prvku
	SDL_Surface *m_bitmap;		// bitmapa tlaèítka
	SDL_Rect m_rectPoz;		// obklopujici ramecek	(umisteni, rozmery)
	GBase *m_pParent;	// rodiè prvku
	TTF_Font *m_font;
};

#endif
