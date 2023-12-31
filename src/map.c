#include "map.h"

struct Map create_map(int width, int height) {
  struct Map ret = {0};

  ret.width = width;
  ret.height = height;
  sprintf(ret.name, "new_map");

  return ret;
}

