#ifndef KEYMAP_H
#define KEYMAP_H

#include "SDL2/SDL.h"

#include "tiler.h"

#define MAX_KEYBINDS (64)
#define KEYBIND_DESC_LEN (256)

struct Keybind {
  char* desc;
  SDL_Keycode key;
  void (*proc)(struct Tiler*);
};

struct Keybind* get_keybinds(void);

#endif /* KEYMAP_H */

