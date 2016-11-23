#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include <string>
#include "defines.h"

using namespace std;

int getRnd(int max);
void drawText(TTF_Font *font, SDL_Color color, const std::string text, int x, int y);
bool rectIntersection(SDL_Rect *rect1, SDL_Rect *rect2);
bool pointInRect(int x, int y, SDL_Rect *rect);
inline Uint8 getByte(Uint32 word, Uint8 order) { return (word >> (8 * order)) & 0xff; }

#endif
