#ifndef BLOCK_H
#define BLOCK_H

#include "block_type.h"
#include "tiler.h"

void delete_current_block(struct Tiler* app);
void add_block(struct Tiler* app);
struct Block create_block(int x, int y);
void draw_block(struct Tiler app, struct Block b);
void draw_block_highlight(struct Tiler app);
void get_block(struct Tiler* app);

#endif /* BLOCK_H */

