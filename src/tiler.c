#include "SDL2/SDL.h"
#include "stdio.h"

#include "tiler.h"
#include "bottom_bar.h"

static float dpi = 1.0f;

float get_dpi(void) {
  float dpi;
  SDL_GetDisplayDPI(0, &dpi, NULL, NULL);
  return dpi / 96.0f;
}

float scale(void) { return dpi; }

int main(int argc, char** argv) {
  struct Tiler app = {0};
  SDL_DisplayMode dm;
  SDL_Event event;
  unsigned char running = 1;
#ifdef _WIN32
  {
    HINSTANCE lib = LoadLibrary("user32.dll");
    int (*SetProcessDPIAware)(void) = (void*) GetProcAddress(lib, "SetProcessDPIAware");
    SetProcessDPIAware();
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

  dpi = get_dpi();

  bottom_bar_init(&app);
  SDL_SetRenderDrawColor(app.renderer, 255, 60, 60, 255);
	SDL_RenderClear(app.renderer);
	SDL_RenderPresent(app.renderer);
  /* Main loop */
  for (;running;) {
    /* Check for events. */
    for (;SDL_PollEvent(&event) != 0;) {
      switch (event.type) {
        case SDL_QUIT: {
          running = 0;
          break;
        }
        case SDL_WINDOWEVENT_SIZE_CHANGED: /* fallthrough */
        case SDL_WINDOWEVENT: {
          switch (event.window.event) {
            case SDL_WINDOWEVENT_RESIZED: {
              app.window_width = event.window.data1;
              app.window_height = event.window.data2;
              break;
            }
            default: {
              break;
            }
          }
        }
        /* No reason to update screen if there's no events. */
        default: {
          SDL_SetRenderDrawColor(app.renderer, 20, 20, 20, 255);
          SDL_RenderClear(app.renderer);
          bottom_bar_update();
          bottom_bar_draw();
          SDL_RenderPresent(app.renderer);
          break;
        }
      }
    }
    SDL_Delay(1000 / TARGET_FPS);
  }

  SDL_DestroyWindow(app.window);
  SDL_DestroyRenderer(app.renderer);
  SDL_Quit();
  return 0;
}

