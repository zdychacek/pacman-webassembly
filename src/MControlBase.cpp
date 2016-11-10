#include "MControlBase.h"

MControlBase::MControlBase(GBase *parent):
	m_pParent(parent),
	m_font(nullptr)
{
}

MControlBase::~MControlBase() {
	SDL_FreeSurface(m_bitmap);
	m_bitmap = nullptr;
}

bool MControlBase::isInRect(int x, int y)const {
	if((x < m_rectPoz.x + m_rectPoz.w) && (x > m_rectPoz.x) &&
		(y > m_rectPoz.y) && (y < m_rectPoz.y + m_rectPoz.h)) return true;
	else return false;
}

void MControlBase::draw(SDL_Surface *screen) {
}

bool MControlBase::mouseLButtonDown(int x, int y) {
	return true;
}

bool MControlBase::mouseLButtonUp(int x, int y) {
	return true;
}

bool MControlBase::mouseRButtonDown(int x, int y) {
	return true;
}

bool MControlBase::mouseRButtonUp(int x, int y) {
	return true;
}

bool MControlBase::mouseMove(int x, int y) {
	return true;
}

void MControlBase::keyDown(Uint8 key) {
}

void MControlBase::keyUp(Uint8 key) {
}

void MControlBase::move(int cx, int cy) {
	m_rectPoz.x += cx;
	m_rectPoz.y += cy;
}
