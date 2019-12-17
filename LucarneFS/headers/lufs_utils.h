#ifndef LUFS_UTILS_H
#define LUFS_UTILS_H
#include <stdint.h>
#include <stdio.h>

struct LuFS_block {
    uint8_t data[512];
} __attribute__((packed));
struct LuFS_block * drv_get_block(uint64_t LBA48, FILE * drive);
uint64_t drv_get_last_LBA(FILE * drive);
#endif
