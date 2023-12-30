#ifndef BOTTOM_BAR_H
#define BOTTOM_BAR_H

#include "tiler.h"

#define BB_MIN_HEIGHT (70)
#define BB_MIN_WIDTH (690)
#define BB_MARGIN_X (0.02f)

struct BottomBar {
  struct Tiler* app;
  SDL_Rect r;
  int height;
};

void bottom_bar_init(struct Tiler* t);
void bottom_bar_update();
void bottom_bar_draw();

#endif /* BOTTOM_BAR_H */

