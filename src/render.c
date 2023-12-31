#include "SDL2/SDL.h"
#include "stdlib.h"

void draw_circle(SDL_Renderer *renderer, int x, int y, int radius) {
  int w, h;
  for (w = 0; w < radius * 2; w++) {
    for (h = 0; h < radius * 2; h++) {
      int dx = radius - w; /* horizontal offset */
      int dy = radius - h; /* vertical offset */
      if ((dx * dx + dy * dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, x + dx, y + dy);
      }
    }
  }
}

