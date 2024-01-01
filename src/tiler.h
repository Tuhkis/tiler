#ifndef TILER_H
#define TILER_H

#include "math.h"
#include "SDL2/SDL.h"
#include "stdio.h"

#include "block_type.h"
#include "font.h"
#include "map.h"

#ifdef _WIN32
  #define WIN32_LEAN_AND_MEAN
  #include "windows.h"
#endif /* _WIN32 */

#define TARGET_FPS (60.0f)
#define TILE_SIZE (50 * scale() * zoom())

struct Tiler {
  float cam_x, cam_y;
  Font* ui_font;
  int window_height;
  int window_width;
  SDL_Renderer* renderer;
  SDL_Window* window;
  struct Block* current_block;
  struct Map map;
  unsigned char running;
};

float scale(void);
float zoom(void);
void change_zoom(float amt);
void quit_app(struct Tiler* app);

#endif /* TILER_H */

