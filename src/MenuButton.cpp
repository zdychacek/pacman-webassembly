#include "MenuButton.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Game.h"

MenuButton::MenuButton() : GameObject(), m_callback(nullptr), m_bReleased(true)
{
}

void MenuButton::load(std::unique_ptr<LoaderParams> const &pParams)
{
  m_callbackID = pParams->getCallbackID();
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_numFrames = pParams->getNumFrames();
	m_currentFrame = MOUSE_OUT;
	m_position = Vector2D(pParams->getX(),pParams->getY());
}

void MenuButton::draw()
{
  TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
					m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_angle, m_alpha);
}

void MenuButton::update()
{
	m_position += m_velocity;
  m_currentFrame = static_cast<int>((SDL_GetTicks() / (1000 / 3)) % m_numFrames);

  Vector2D *pMousePos = TheInputHandler::Instance()->getMousePosition();

  if (pMousePos->getX() < (m_position.getX() + m_width) && pMousePos->getX() > m_position.getX() && pMousePos->getY() < (m_position.getY() + m_height) && pMousePos->getY() > m_position.getY())
  {
    if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
    {
      m_currentFrame = CLICKED;

      if (m_callback != nullptr)
      {
				m_callback();
      }

      m_bReleased = false;
    }
    else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
    {
      m_bReleased = true;
      m_currentFrame = MOUSE_OVER;
    }
  }
  else
  {
    m_currentFrame = MOUSE_OUT;
  }
}

void MenuButton::clean() {

}
