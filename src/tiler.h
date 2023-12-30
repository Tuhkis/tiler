#ifndef TILER_H
#define TILER_H

#ifdef _WIN32
  #define WIN32_LEAN_AND_MEAN
  #include "windows.h"
#endif /* _WIN32 */

#define TARGET_FPS (120)

struct Tiler {
  SDL_Window* window;
  SDL_Renderer* renderer;
  int window_width;
  int window_height;
};

float scale(void);

#endif /* TILER_H */

