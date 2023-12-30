#ifndef BOTTOM_BAR_H
#define BOTTOM_BAR_H

#include "tiler.h"

#define BB_MAX_HEIGHT (62 * scale())
#define BB_MIN_HEIGHT (32 * scale())
#define BB_MIN_WIDTH (500 * scale())
#define BB_MARGIN_X (0.02f)
#define BB_HEIGHT (0.1f)

struct BottomBar {
  int height;
  SDL_Rect r;
  struct Tiler* app;
};

void bottom_bar_init(struct Tiler* t);
void bottom_bar_update(void);
void bottom_bar_draw(void);

#endif /* BOTTOM_BAR_H */

