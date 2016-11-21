#ifndef DEFINES_H
#define DEFINES_H

struct Point
{
  Point(int xx, int yy) : x(xx),
			  y(yy) {}
  Point() : x(0),
	    y(0) {}
  int x,
      y;
  inline Point &operator=(const Point &p)
  {
    x = p.x;
    y = p.y;
    return *this;
  }
};

inline bool operator==(const Point &p1, const Point &p2)
{
  return ((p1.x == p2.x) && (p1.y == p2.y));
}

inline bool operator!=(const Point &p1, const Point &p2)
{
  return (!((p1.x == p2.x) && (p1.y == p2.y)));
}

typedef unsigned int UINT;

#define _APPNAME "PacMan 2006"
#define _INIFILE "config.cfg"

#define PAC_MOUTH_ANIM_TIME 80
#define PAC_DYING_ANIM_TIME 100
#define PAC_APPEARING_ANIM_TIME 200
#define PAC_MAX_DYING_FRAMES 8
#define PAC_MOVING_TIME 37
#define PAC_VELOCITY_NORMAL 3
#define PAC_NEW_LIVES_COUNT 3
#define PAC_MAX_BLIKS 11

#define MAX_LEVELS 7
#define MAX_GHOSTS 5
#define NUM_BORCU_IN_TOPLIST 5

#define MAP_X 28
#define MAP_Y 20
#define MAP_TILE_SIZE 18

#define GHOST_VELOCITY_NORMAL 3
#define GHOST_MOVING_TIME 40
#define GHOST_ANIM_TIME 50
#define GHOST_AFFRAID_TIME 15000

#define SCORE_GHOST_DEAD 200
#define SCORE_EAT_DOT 40
#define SCORE_TAKE_BOOST 100

#define CURSOR_MAX_FRAMES 23
#define CURSOR_ANIM_TIME 50

// struktura reprezentujici konfiguraèní soubor
struct inifile
{
  int resX,
      resY,
      bpp;
  bool fs,
      sounds,
      effects;
};

#endif
