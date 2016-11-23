#include <iostream>
#include "defines.h"
#include "utils.h"
#include "Game.h"

int getRnd(int max)
{
  return (rand() % max);
}

void drawText(TTF_Font *font, SDL_Color color, const std::string text, int x, int y)
{
  SDL_Surface *text_surface = TTF_RenderText_Blended(font, text.c_str(), color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), text_surface);

  SDL_Rect text_dest = {x, y, 0, 0};
  SDL_QueryTexture(texture, nullptr, nullptr, &text_dest.w, &text_dest.h);
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), texture, nullptr, &text_dest);

  SDL_FreeSurface(text_surface);
}

bool rectIntersection(SDL_Rect *rect1, SDL_Rect *rect2)
{
  double left1, left2, top1, top2, right1, right2, bottom1, bottom2;

  left1 = rect1->x;
  top1 = rect1->y;
  right1 = rect1->x + rect1->w;
  bottom1 = rect1->y + rect1->h;

  left2 = rect2->x;
  top2 = rect2->y;
  right2 = rect2->x + rect2->w;
  bottom2 = rect2->y + rect2->h;

  if (bottom1 < top2)
    return false;
  if (top1 > bottom2)
    return false;
  if (right1 < left2)
    return false;
  if (left1 > right2)
    return false;

  return true;
}

bool pointInRect(int x, int y, SDL_Rect *rect)
{
  return (x < rect->x + rect->w) && (x > rect->x) && (y > rect->y) && (y < rect->y + rect->h);
}
