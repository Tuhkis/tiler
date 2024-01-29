#include "SDL2/SDL.h"
#include "stdio.h"

#include "font.h"
#include "help.h"
#include "keymap.h"
#include "style.h"

static struct HelpScreen screen = {0};

void help_screen_init(struct Tiler* app) {
  screen.scroll = 0.0f;
  screen.app = app;
  screen.keybinds = get_keybinds();
}

void help_screen_toggle(struct Tiler* app) {
  (void) app;
  screen.visible = !screen.visible;
}

char help_process_scroll(int mouse_x, int mouse_y, float scroll) {
  /* Check if mouse is in screen. */
  if (screen.visible) {
    screen.scroll += scroll * 225.0f;
    if (screen.scroll > 0.0f) screen.scroll = 0.0f;
    return 1;
  }
  return 0;
}

void help_screen_draw(void) {
  if (screen.visible) {
    int i;
    SDL_Rect r0;
    float border = 10.0f * scale();

    r0.w = screen.app->window_width * 0.4f;
    if (r0.w < 425 * scale()) r0.w = 425 * scale();
    r0.h = screen.app->window_height * 0.7f;
    if (r0.h < 333 * scale()) r0.h = 333 * scale();
    r0.x = (screen.app->window_width * 0.5f) - r0.w * 0.5f;
    r0.y = (screen.app->window_height * 0.5f) - r0.h * 0.5f;

    screen.r.w = r0.w - floor(border);
    screen.r.h = r0.h - floor(border);
    screen.r.x = r0.x + floor(border * 0.5f);
    screen.r.y = r0.y + floor(border * 0.5f);

    SDL_SetRenderDrawColor(screen.app->renderer, ACCENT_COLOR);
    SDL_RenderFillRect(screen.app->renderer, &r0);
    SDL_SetRenderDrawColor(screen.app->renderer, BG_COLOR);
    SDL_RenderFillRect(screen.app->renderer, &screen.r);
    SDL_RenderSetClipRect(screen.app->renderer, &screen.r);
    SDL_SetRenderDrawColor(screen.app->renderer, TEXT_COLOR);
    render_text(screen.app->renderer, screen.app->ui_font, screen.r.x + 4, screen.r.y + 28 * scale() + screen.scroll, "Keybinds:");
    for (i = 0; i < MAX_KEYBINDS; ++i) {
      /* Hope and dream that this isn't exceeded... */
      char buf[512];
      if (screen.keybinds[i].desc == NULL) break;
      sprintf(buf, "%s: %s", SDL_GetKeyName(screen.keybinds[i].key), screen.keybinds[i].desc);
      render_text(screen.app->renderer, screen.app->ui_font, screen.r.x + 4, screen.r.y + scale() * 36 * (i + 2) + screen.scroll, buf);
    }
    SDL_SetRenderDrawColor(screen.app->renderer, ACCENT_COLOR);
    screen.r.x += floor(screen.r.w - 10 * scale());
    screen.r.y += (-screen.scroll * 50.0f) / screen.r.h + 4 * scale()  ;
    screen.r.w = floor(8 * scale());
    screen.r.h = floor(64 * scale());

    SDL_RenderFillRect(screen.app->renderer, &screen.r);
    SDL_RenderSetClipRect(screen.app->renderer, NULL);
  }
}

