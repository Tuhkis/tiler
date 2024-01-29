#include "stdio.h"

#include "block.h"
#include "render.h"
#include "style.h"

void delete_current_block(struct Tiler* app) {
  printf("Not implemented :shrug:\n");
}

void add_block(struct Tiler* app) {
  app->map.blocks[0] = create_block((app->mouse_x + app->cam_x) / TILE_SIZE, (app->mouse_y + app->cam_y) / TILE_SIZE);
  app->current_block = &app->map.blocks[0];
}

struct Block create_block(int x, int y) {
  struct Block ret;

  ret.exist = 1;
  ret.x = x;
  ret.y = y;
  ret.w = 1;
  ret.h = 1;

  return ret;
}

void draw_block(struct Tiler app, struct Block b) {
  SDL_Rect r;
  if (!b.exist) return;
  SDL_SetRenderDrawColor(app.renderer, RGB(255, 0, 0));
  r.x = b.x * TILE_SIZE - app.cam_x;
  r.y = b.y * TILE_SIZE - app.cam_y;
  r.w = b.w * TILE_SIZE;
  r.h = b.h * TILE_SIZE;
  SDL_RenderFillRect(app.renderer, &r);
}

void draw_block_highlight(struct Tiler app) {
  if (app.current_block == NULL) return;
  SDL_SetRenderDrawColor(app.renderer, ACCENT_COLOR);
  draw_circle(app.renderer,
    (TILE_SIZE * app.current_block->x + TILE_SIZE * 0.5f * app.current_block->w) - app.cam_x,
    TILE_SIZE * app.current_block->y - app.cam_y,
    7);
  draw_circle(app.renderer,
    (TILE_SIZE * app.current_block->x + TILE_SIZE * 0.5f * app.current_block->w) - app.cam_x,
    (TILE_SIZE * app.current_block->y + TILE_SIZE * app.current_block->h) - app.cam_y,
    7);
  draw_circle(app.renderer,
    TILE_SIZE * app.current_block->x - app.cam_x,
    (TILE_SIZE * app.current_block->y + TILE_SIZE * 0.5f * app.current_block->w) - app.cam_y,
    7);
  draw_circle(app.renderer,
    (TILE_SIZE * app.current_block->x + TILE_SIZE * app.current_block->w) - app.cam_x,
    (TILE_SIZE * app.current_block->y + TILE_SIZE * 0.5f * app.current_block->h) - app.cam_y,
    7);
}

