#include "SDL2/SDL.h"
#include "stdio.h"

#include "font.h"
#include "help.h"
#include "keymap.h"
#include "style.h"

static struct HelpScreen screen = {0};

void help_screen_init(struct Tiler* app) {
  screen.app = app;
  screen.keybinds = get_keybinds();
}

void help_screen_toggle(struct Tiler* app) {
  (void) app;
  screen.visible = !screen.visible;
}

void help_screen_draw(void) {
  if (screen.visible) {
    int i;
    SDL_Rect r0;
    SDL_Rect r1;
    float border = 10.0f * scale();

    r0.w = screen.app->window_width * 0.4f;
    r0.h = screen.app->window_height * 0.7f;
    r0.x = (screen.app->window_width * 0.5f) - r0.w * 0.5f;
    r0.y = (screen.app->window_height * 0.5f) - r0.h * 0.5f;

    r1.w = r0.w - floor(border);
    r1.h = r0.h - floor(border);
    r1.x = r0.x + floor(border * 0.5f);
    r1.y = r0.y + floor(border * 0.5f);

    SDL_SetRenderDrawColor(screen.app->renderer, ACCENT_COLOR);
    SDL_RenderFillRect(screen.app->renderer, &r0);
    SDL_SetRenderDrawColor(screen.app->renderer, BG_COLOR);
    SDL_RenderFillRect(screen.app->renderer, &r1);
    SDL_SetRenderDrawColor(screen.app->renderer, TEXT_COLOR);
    render_text(screen.app->renderer, screen.app->ui_font, r1.x + 4, r1.y + 26, "Keybinds:");
    for (i = 0; i < MAX_KEYBINDS; ++i) {
      /* Hope and dream that this isn't exceeded... */
      char buf[512];
      if (screen.keybinds[i].desc == NULL) break;
      sprintf(buf, "%s: %s", SDL_GetKeyName(screen.keybinds[i].key), screen.keybinds[i].desc);
      render_text(screen.app->renderer, screen.app->ui_font, r1.x + 4, r1.y + 26 * (i + 2) + 4, buf);
    }
  }
}

