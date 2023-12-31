#ifndef MAP_H
#define MAP_H

#include "SDL2/SDL.h"

#include "block_type.h"

#define MAX_BLOCKS (1024)
#define MAP_MAX_NAME_LEN (1024)

struct Map {
  char name[MAP_MAX_NAME_LEN];
  int width, height;
  struct Block blocks[MAX_BLOCKS];
};

struct Map create_map(int width, int height);

#endif /* MAP_H */

