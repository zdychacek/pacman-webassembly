#include <iostream>
#include <assert.h>
#include "MainMenuState.h"
#include "StateParser.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"
#include "MenuButton.h"

using namespace std;

const string MainMenuState::s_menuID = "MENU";

// Callbacks
void MainMenuState::s_menuToPlay()
{
  //TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
  //cout << this;

#ifndef __EMSCRIPTEN__
  TheGame::Instance()->quit();
#endif
}

// end callbacks

void MainMenuState::update()
{
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
  {
    s_menuToPlay();
  }

  for_each(m_gameObjects.begin(), m_gameObjects.end(), [](auto gameObject) {
    if (gameObject != nullptr)
    {
      gameObject->update();
    }
  });
}

void MainMenuState::render()
{
  if (m_loadingComplete && !m_gameObjects.empty())
  {
    for_each(m_gameObjects.begin(), m_gameObjects.end(), [](auto gameObject) {
      gameObject->draw();
    });
  }
}

bool MainMenuState::onEnter()
{
  // parse the state
  StateParser stateParser;
  stateParser.parseState("assets/states.xml", s_menuID, &m_gameObjects, &m_textureIDList);

  m_callbacks.push_back(s_menuToPlay);
  m_callbacks.push_back(s_exitFromMenu);

  // set the callbacks for menu items
  setCallbacks(m_callbacks);

  m_loadingComplete = true;
  std::cout << "Entering MenuState" << std::endl;

  return true;
}

bool MainMenuState::onExit()
{
  m_exiting = true;

  // clean the game objects
  if (m_loadingComplete && !m_gameObjects.empty())
  {
    m_gameObjects.back()->clean();
    m_gameObjects.pop_back();
  }

  m_gameObjects.clear();

  // clear the texture manager
  std::for_each(m_textureIDList.begin(), m_textureIDList.end(), [](auto texture) {
    TheTextureManager::Instance()->clearFromTextureMap(texture);
  });

  // reset the input handler
  TheInputHandler::Instance()->reset();

  std::cout << "Exiting MenuState" << std::endl;

  return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback> &callbacks)
{
  std::for_each(m_gameObjects.begin(), m_gameObjects.end(), [callbacks](auto gameObject) {
    // if they are of type MenuButton then assign a callback based on the id passed in from the file
    if (dynamic_cast<MenuButton *>(gameObject))
    {
      MenuButton *pButton = dynamic_cast<MenuButton *>(gameObject);
      pButton->setCallback(callbacks[pButton->getCallbackID()]);
    }
  });
}
