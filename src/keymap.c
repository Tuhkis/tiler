#include "SDL2/SDL.h"

#include "help.h"
#include "keymap.h"

void zoom_in(struct Tiler* app);
void zoom_out(struct Tiler* app);

static struct Keybind keys[MAX_KEYBINDS] = {
  {"Open help screen.", SDLK_TAB, help_screen_toggle},
  {"Close program.", SDLK_ESCAPE, quit_app},
  {"Zoom in.", SDLK_PLUS, zoom_in},
  {"Zoom out.", SDLK_MINUS, zoom_out},
  {NULL, 0, NULL}
};

struct Keybind* get_keybinds(void) {
  return keys;
}

void zoom_in(struct Tiler* app) {
  change_zoom(0.5f * scale());
}

void zoom_out(struct Tiler* app) {
  change_zoom(-0.5f * scale());
}

