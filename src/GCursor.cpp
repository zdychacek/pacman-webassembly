#include <iostream>
#include <stdexcept>
#include "GCursor.h"
#include "TextureManager.h"
#include "GRun.h"

GCursor::GCursor():
	m_nX(0),
	m_nY(0),
	m_nAnimFrame(0)
{
	SDL_GetMouseState(&m_nX, &m_nY);

	m_nLastAnim = SDL_GetTicks();

	if (!TheTextureManager::Instance()->load("assets/gfx/cursor.bmp", "cursor", TheGRun::Instance()->getRenderer())) {
		throw std::runtime_error("Unable to load cursor texture.");
	}
}

void GCursor::anim () {
	m_nAnimFrame = int(((SDL_GetTicks() / CURSOR_ANIM_TIME) % CURSOR_MAX_FRAMES));
}

void GCursor::draw() {
	TheTextureManager::Instance()
		->drawFrame("cursor", getX(), getY(), 32, 32, 1, m_nAnimFrame, TheGRun::Instance()->getRenderer(), 0, 255);
}
