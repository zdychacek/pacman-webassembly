#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include <string>
#include "defines.h"

using namespace std;

int getRnd(int max);
bool drawText(TTF_Font *font, SDL_Color color, const char *string, int x, int y);
bool rectIntersection(SDL_Rect *rect1, SDL_Rect *rect2);
bool pointInRect(int x, int y, SDL_Rect *rect);

#endif
