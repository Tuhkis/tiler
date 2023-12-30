#include "SDL2/SDL.h"

#include "bottom_bar.h"

static struct BottomBar bar = {0};

void bottom_bar_init(struct Tiler* t) {
  bar.app = t;
}

void bottom_bar_update() {
  bar.height = bar.app->window_height * BB_HEIGHT;
  if (bar.height < BB_MIN_HEIGHT) bar.height = BB_MIN_HEIGHT;
  if (bar.height > BB_MAX_HEIGHT) bar.height = BB_MAX_HEIGHT;

  bar.r.x = bar.app->window_width * BB_MARGIN_X;
  bar.r.y = bar.app->window_height - bar.height;

  bar.r.w = bar.app->window_width - bar.r.x * 2;
  bar.r.x = bar.r.w > BB_MIN_WIDTH ?
    bar.app->window_width * BB_MARGIN_X : 0;
  bar.r.w = bar.app->window_width - bar.r.x * 2;

  bar.r.h = bar.height;
}

void bottom_bar_draw() {
  SDL_SetRenderDrawColor(bar.app->renderer, 240, 240, 240, 255);
  SDL_RenderFillRect(bar.app->renderer, &bar.r);
}

