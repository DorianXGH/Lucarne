#ifndef FONT_DESC_H
#define FONT_DESC_H
#include "../drivers/screen.h"
#include <stdint.h>

struct font_desc {
    struct sprite * chars;
    uint8_t         charmap[256];
};

#endif
