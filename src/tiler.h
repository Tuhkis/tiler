#ifndef TILER_H
#define TILER_H

#define TARGET_FPS (40)

struct Tiler {
  SDL_Window* window;
  SDL_Renderer* renderer;
  int window_width;
  int window_height;
};

#endif /* TILER_H */

