#ifndef FONT_H
#define FONT_H

#include "stb_truetype.h"

typedef struct {
  stbtt_fontinfo* info;
  stbtt_packedchar* chars;
  SDL_Texture* atlas;
  int texture_size;
  float size;
  float scale;
  int ascent;
  int baseline;
} Font;

Font* open_font(SDL_Renderer* renderer, const char* filename, float size);
void close_font(Font* font);
void render_text(SDL_Renderer* renderer, Font* font, float x, float y, const char *text);

#endif /* FONT_H */

