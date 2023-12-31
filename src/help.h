#ifndef HELP_H
#define HELP_H

#include "keymap.h"
#include "tiler.h"

struct HelpScreen {
  struct Keybind* keybinds;
  struct Tiler* app;
  float scroll;
  SDL_Rect r;
  unsigned char visible;
};

char help_process_scroll(float mouse_x, float mouse_y, float scroll);
void help_screen_init(struct Tiler* app);
void help_screen_toggle(struct Tiler* app);
void help_screen_draw(void);

#endif /* HELP_H */

