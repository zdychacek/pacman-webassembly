#include "GBase.h"

GBase::GBase():
	m_pFocusCtrl(NULL)
{
}

GBase::~GBase() {
	m_pFocusCtrl = NULL;
}

void GBase::move() {
}

void GBase::render(SDL_Surface *screen) {
}

void GBase::keyDown(Uint8 key) {
}

void GBase::keyUp(Uint8 key) {
}

void GBase::mouseLButtonDown(int x,int y) {
}

void GBase::mouseLButtonUp(int x,int y) {
}

void GBase::mouseRButtonDown(int x,int y) {
}

void GBase::mouseRButtonUp(int x,int y) {
}

void GBase::mouseMove(int x,int y) {
}