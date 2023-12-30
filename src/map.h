#ifndef MAP_H
#define MAP_H

#include "SDL2/SDL.h"

#define MAX_BOXES (512)
#define MAP_MAX_NAME_LEN (1024)

struct Map {
  char name[MAP_MAX_NAME_LEN];
  int width, height;
  SDL_Rect boxes[MAX_BOXES];
};

struct Map create_map(int width, int height);

#endif /* MAP_H */

