#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "utils.h"

TextureManager *TextureManager::s_pInstance = nullptr;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer *pRenderer, Uint32 const *colorKey)
{
  SDL_Surface *pTempSurface = IMG_Load(fileName.c_str());

  if (colorKey != nullptr)
  {
    const Uint8 red = getByte(*colorKey, 2);
    const Uint8 green = getByte(*colorKey, 1);
    const Uint8 blue = getByte(*colorKey, 0);

    SDL_SetColorKey(
	pTempSurface,
	SDL_TRUE,
	SDL_MapRGB(pTempSurface->format, red, green, blue));
  }

  if (pTempSurface == 0)
  {
    std::cout << IMG_GetError();

    return false;
  }

  SDL_Texture *pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

  SDL_FreeSurface(pTempSurface);

  if (pTexture != 0)
  {
    m_textureMap[id] = pTexture;

    return true;
  }

  return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer *pRenderer, SDL_RendererFlip flip)
{
  SDL_Rect srcRect;
  SDL_Rect destRect;

  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, double angle, int alpha, SDL_RendererFlip flip)
{
  SDL_Rect srcRect;
  SDL_Rect destRect;
  srcRect.x = width * currentFrame;
  srcRect.y = height * currentRow;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
  SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer)
{
  SDL_Rect srcRect;
  SDL_Rect destRect;
  srcRect.x = margin + (spacing + width) * currentFrame;
  srcRect.y = margin + (spacing + height) * currentRow;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::clearTextureMap()
{
  m_textureMap.clear();
}

void TextureManager::clearFromTextureMap(std::string id)
{
  m_textureMap.erase(id);
}
