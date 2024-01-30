#include "SDL2/SDL.h"

#include "block.h"
#include "help.h"
#include "keymap.h"

void zoom_in(struct Tiler* app);
void zoom_out(struct Tiler* app);

static struct Keybind keys[] = {
  {"Open/Close help screen.", SDLK_TAB, help_screen_toggle},
  {"Close program.", SDLK_ESCAPE, quit_app},
  {"Zoom in.", SDLK_PLUS, zoom_in},
  {"Zoom out.", SDLK_MINUS, zoom_out},
  {"Add new block at mouse cursor.", SDLK_LCTRL, add_block},
  {"Delete chosen block.", SDLK_DELETE, delete_current_block},
  {"Choose the block under the mouse.", SDLK_SPACE, get_block},
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

