#include "SDL2/SDL.h"

#include "help.h"
#include "keymap.h"

static struct Keybind keys[MAX_KEYBINDS] = {
  {"Open help screen.", SDLK_TAB, help_screen_toggle},
  {"Close program.", SDLK_ESCAPE, quit_app},
  {NULL, 0, NULL}
};

struct Keybind* get_keybinds(void) {
  return keys;
}

