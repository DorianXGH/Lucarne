#ifndef LUFS_UTILS_H
#define LUFS_UTILS_H
#include <stdint.h>
#include <stdio.h>

struct LuFS_block {
    uint8_t data[512];
} __attribute__((packed));
struct virt_drv {
    uint8_t * data;
    uint32_t  capacity;
};

struct LuFS_block * drv_get_block(uint64_t LBA48, struct virt_drv * drive);
uint64_t drv_get_last_LBA(struct virt_drv * drive);
struct LuFS_block * LuFS_get_free_blocks(uint32_t n, struct LuFS_master_block * master, struct virt_drv * drive)
#endif // ifndef LUFS_UTILS_H
