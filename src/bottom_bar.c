#include "SDL2/SDL.h"

#include "bottom_bar.h"
#include "style.h"

static struct BottomBar bar = {0};

int bottom_bar_scroll(int mouse_x, int mouse_y, float scroll) {
  SDL_Point p;
  p.x = mouse_x;
  p.y = mouse_y;
  if (SDL_PointInRect(&p, &bar.r)) {
    bar.scroll += scroll * 125.0f;
    if (bar.scroll > 0.0f) bar.scroll = 0.0f;
    return 1;
  } else {
    return 0;
  }
}

void bottom_bar_init(struct Tiler* t) {
  bar.app = t;
  bar.scroll = 0.0f;
}

void bottom_bar_update(void) {
  bar.height = bar.app->window_height * BB_HEIGHT;
  if (bar.height < BB_MIN_HEIGHT) bar.height = BB_MIN_HEIGHT;
  if (bar.height > BB_MAX_HEIGHT) bar.height = BB_MAX_HEIGHT;

  bar.r.x = bar.app->window_width * BB_MARGIN_X;
  bar.r.y = bar.app->window_height - bar.height - floor(10 * scale());

  bar.r.w = bar.app->window_width - bar.r.x * 2;
  if (bar.r.w < BB_MIN_WIDTH) {
    bar.r.x = 0;
    bar.r.y += floor(10 * scale());
  }
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

  /* Draw bar ui element. */
  SDL_SetRenderDrawColor(bar.app->renderer, ACCENT_COLOR);
  SDL_RenderFillRect(bar.app->renderer, &r);
  SDL_SetRenderDrawColor(bar.app->renderer, BG_COLOR);
  SDL_RenderFillRect(bar.app->renderer, &bar.r);
  bar.r.w -= floor(8 * scale());
  /* Draw elements inside the bar. */
  SDL_RenderSetClipRect(bar.app->renderer, &bar.r);
  SDL_SetRenderDrawColor(bar.app->renderer, ACCENT_COLOR);
  r.x -= floor(bar.scroll * 0.45f) - floor(8 * scale());
  r.w = floor(55 * scale());
  r.h = floor(4 * scale());
  r.y += bar.r.h - floor(4 * scale());
  SDL_RenderFillRect(bar.app->renderer, &r);

  SDL_RenderSetClipRect(bar.app->renderer, NULL);
}

