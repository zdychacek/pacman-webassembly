#ifndef GCURSOR_H
#define GCURSOR_H

#include "utils.h"

class GCursor
{
public:
	GCursor();
	inline void setX(int x) {m_nX = x;}
	inline int getX()const {return m_nX;}
	inline void setY(int y) {m_nY = y;}
	inline int getY()const {return m_nY;}
	void anim();
	void draw();
private:
	int m_nX,
		m_nY,
		m_nAnimFrame,
		m_nLastAnim;
};

#endif
