#include "SDL2/SDL.h"
#include "stdio.h"

#include "stb_truetype.h"

#include "bottom_bar.h"
#include "font.h"
#include "help.h"
#include "keymap.h"
#include "map.h"
#include "render.h"
#include "style.h"
#include "tiler.h"

static float dpi_amt = 1.0f;
static float zoom_amt = 1.0f;

float get_dpi(void) {
  float dpi;
  SDL_GetDisplayDPI(0, &dpi, NULL, NULL);
  return dpi / 96.0f;
}

void change_zoom(float amt) {
  zoom_amt += amt;
  if (zoom_amt < 0.6f) zoom_amt = 0.6f;
  if (zoom_amt > 6.0f) zoom_amt = 6.0f;
}

float zoom(void) { return zoom_amt; }
float scale(void) { return dpi_amt; }

void quit_app(struct Tiler* app) {
  app->running = 0;
}

void draw_grid(struct Tiler* app) {
  unsigned int i;
  int line_width = floor(4.0f * scale() * zoom());
  int line_width_half;
  if (line_width < 2) line_width = 2.0f;
  line_width_half = floor(line_width * 0.5f);
  SDL_SetRenderDrawColor(app->renderer, GRID_COLOR);
  for (i = 0; i < app->map.width + 1; ++i) {
    SDL_Rect r;
    r.x = i * TILE_SIZE - 0.5f * line_width - app->cam_x;
    r.y = -app->cam_y - line_width_half;
    r.w = line_width;
    r.h = app->map.height * TILE_SIZE + line_width;
    SDL_RenderFillRect(app->renderer, &r);
  }
  for (i = 0; i < app->map.height + 1; ++i) {
    SDL_Rect r;
    r.x = -app->cam_x;
    r.y = i * TILE_SIZE - 0.5f * line_width - app->cam_y;
    r.w = app->map.width * TILE_SIZE;
    r.h = line_width;
    SDL_RenderFillRect(app->renderer, &r);
  }
}

int main(int argc, char** argv) {
  struct Tiler app = {0};
  SDL_DisplayMode dm;
  SDL_Event event;
#ifdef _WIN32
  {
    HINSTANCE lib = LoadLibrary("user32.dll");
    int (*SetProcessDPIAware)(void) = (void*) GetProcAddress(lib, "SetProcessDPIAware");
    if (SetProcessDPIAware() == 0) { printf("DPI stuff went wrong (?)\n"); }
  }
#endif /* _WIN32 */

  (void)argc;
  (void)argv;

  /* SDL_Init returns 0 if succesfull. 0 = false, 1 = true. */
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
    printf((char*)"Could not init SDL2.\nError: %s\n", (char*)SDL_GetError());
    return -1;
  }

  SDL_GetCurrentDisplayMode(0, &dm);
  app.window_width = dm.w * 0.67f;
  app.window_height = dm.h * 0.72,
  app.window = SDL_CreateWindow((char*)"tiler",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    app.window_width, app.window_height,
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_HIDDEN);
  if (!app.window) {
    printf((char*)"Could not create window.\nError: %s\n", (char*)SDL_GetError());
    SDL_Quit();
    return -1;
  }
  SDL_ShowWindow(app.window);

  app.renderer = SDL_CreateRenderer(app.window, -1,
    SDL_RENDERER_ACCELERATED);
  if (!app.renderer) {
    printf((char*)"Could not create renderer.\nError: %s\n", (char*)SDL_GetError());
    SDL_Quit();
    return -1;
  }

  dpi_amt = get_dpi();

  bottom_bar_init(&app);
  help_screen_init(&app);
  SDL_SetRenderDrawColor(app.renderer, 255, 60, 60, 255);
	SDL_RenderClear(app.renderer);
	SDL_RenderPresent(app.renderer);
	app.cam_x = 0.0f;
	app.cam_y = 0.0f;
	app.map = create_map(16, 13);
	app.ui_font = open_font(app.renderer, "font.ttf", 32 * scale());
	app.running = 1;
  /* Main loop */
  for (;app.running;) {
    /* Check for events. */
    for (;SDL_PollEvent(&event) != 0;) {
      switch (event.type) {
        case SDL_QUIT: {
          app.running = 0;
          break;
        }
        case SDL_KEYDOWN: {
          int i;
          struct Keybind* binds = get_keybinds();
          for (i = 0; i < MAX_KEYBINDS; ++i) {
            if (binds[i].proc == NULL) break;
            if (event.key.keysym.sym == binds[i].key) binds[i].proc(&app);
          }
          break;
        }
        /* Mouse wheel events */
        case SDL_MOUSEWHEEL: {
          /* int mouse_x, mouse_y; */

          change_zoom(event.wheel.y * 0.075f * scale());
          if (event.wheel.x > 0.1f || event.wheel.x < - 0.1f)
            app.cam_x += event.wheel.x * 0.075f * scale();

          /* SDL_GetMouseState(&mouse_x, &mouse_y); */
        }
        case SDL_MOUSEMOTION: {
          if (event.motion.state & SDL_BUTTON_LMASK) {
            app.cam_x -= event.motion.xrel;
            app.cam_y -= event.motion.yrel;
          }
        }
        /* Window events */
        case SDL_WINDOWEVENT: {
          switch (event.window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED: /* fallthrough */
            case SDL_WINDOWEVENT_RESIZED: {
              app.window_width = event.window.data1;
              app.window_height = event.window.data2;
            }
            default: {
            }
          }
          /* Don't break here. */
        }
        /* No reason to update screen if there's no events.     *
         * All change in the view should be caused by the user. */
        default: {
          char name_buf[1024] = {0};
          SDL_Rect temp;
          temp.x = floor(zoom() * (12.5f) - app.cam_x) - 1;
          temp.y = floor(zoom() * (12.5f) - app.cam_y) - 1;
          temp.w = floor(0.5f * TILE_SIZE);
          temp.h = floor(0.5f * TILE_SIZE);

          SDL_SetRenderDrawColor(app.renderer, BG_COLOR);
          SDL_RenderClear(app.renderer);
          draw_grid(&app);
          bottom_bar_update();
          SDL_RenderFillRect(app.renderer, &temp);
          SDL_SetRenderDrawColor(app.renderer, RGB(242, 242, 242));
          sprintf(name_buf, "%s; (%d, %d)", app.map.name, app.map.width, app.map.height);
          render_text(app.renderer, app.ui_font,
            floor(zoom() - app.cam_x), floor((-8 * zoom()) - app.cam_y),
            name_buf);
          bottom_bar_draw();
          help_screen_draw();
          SDL_RenderPresent(app.renderer);
        }
      }
    }
    SDL_Delay(1000 / TARGET_FPS);
  }

  close_font(app.ui_font);

  SDL_DestroyWindow(app.window);
  SDL_DestroyRenderer(app.renderer);
  SDL_Quit();
  return 0;
}

