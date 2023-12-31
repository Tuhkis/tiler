#include "SDL2/SDL.h"

#include "bottom_bar.h"
#include "style.h"

static struct BottomBar bar = {0};

void bottom_bar_init(struct Tiler* t) {
  bar.app = t;
}

void bottom_bar_update(void) {
  bar.height = bar.app->window_height * BB_HEIGHT;
  if (bar.height < BB_MIN_HEIGHT) bar.height = BB_MIN_HEIGHT;
  if (bar.height > BB_MAX_HEIGHT) bar.height = BB_MAX_HEIGHT;

  bar.r.x = bar.app->window_width * BB_MARGIN_X;
  bar.r.y = bar.app->window_height - bar.height - (10 * scale());

  bar.r.w = bar.app->window_width - bar.r.x * 2;
  bar.r.x = bar.r.w > BB_MIN_WIDTH ?
    bar.app->window_width * BB_MARGIN_X : 0;
  bar.r.w = bar.app->window_width - bar.r.x * 2;

  bar.r.h = bar.height;
}

void bottom_bar_draw(void) {
  SDL_Rect r;
  float border = floor(4 * scale());
  r.x = bar.r.x - border;
  r.y = bar.r.y - border;
  r.w = bar.r.w + border * 2;
  r.h = bar.r.h + border * 2;

  SDL_SetRenderDrawColor(bar.app->renderer, ACCENT_COLOR);
  SDL_RenderFillRect(bar.app->renderer, &r);
  SDL_SetRenderDrawColor(bar.app->renderer, BG_COLOR);
  SDL_RenderSetClipRect(bar.app->renderer, &bar.r);
  SDL_RenderFillRect(bar.app->renderer, &bar.r);
  SDL_RenderSetClipRect(bar.app->renderer, NULL);
}

