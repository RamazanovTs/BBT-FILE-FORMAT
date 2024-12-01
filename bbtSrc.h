#ifndef BBT_SRC_H
#define BBT_SRC_H

#include <stdint.h>

typedef struct {
    uint32_t signature;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
} Header;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Pixel;

void bbt_creator(uint32_t width, uint32_t height, uint32_t depth, Pixel *pixels);

#endif
