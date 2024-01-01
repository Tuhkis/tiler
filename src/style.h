#ifndef STYLE_H
#define STYLE_H

/* What's better than hacking the C preprocessor for evil? */
#undef RGB
#undef RGBA
#define RGB(r, g, b) r, g, b, 255
#define RGBA(r, g, b, a) r, g, b, a

#define ACCENT_COLOR RGBA(222, 240, 255, 100)
#define BG_COLOR RGB(20, 20, 20)
#define BOTTOM_BAR_COLOR RGB(122, 122, 122)
#define GRID_COLOR RGB(35, 35, 35)
#define TEXT_COLOR RGB(240, 240, 240)

#endif /* STYLE_H */

