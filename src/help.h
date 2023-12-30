#ifndef HELP_H
#define HELP_H

#include "keymap.h"
#include "tiler.h"

struct HelpScreen {
  struct Keybind* keybinds;
  struct Tiler* app;
  unsigned char visible;
};

void help_screen_init(struct Tiler* app);
void help_screen_toggle(struct Tiler* app);
void help_screen_draw(void);

#endif /* HELP_H */

