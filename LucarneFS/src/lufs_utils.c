#include "../headers/lufs_utils.h"
#include "../headers/lucarnefs.h"
#include "../headers/tests.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

uint64_t drv_get_last_LBA(struct virt_drv * drive)
{
    return drive->capacity; // (divide by 512)
}

struct LuFS_block * drv_get_block(uint64_t LBA48, struct virt_drv * drive)
{
    if (LBA48 < drv_get_last_LBA(drive)) {
        struct LuFS_block * blck = (struct LuFS_block *) (drive + (LBA48 * 512));
        return blck;
    } else {
        printf("ERROR : tried to access not present LBA");
    }
}

struct LuFS_block * LuFS_get_free_blocks(uint32_t n, struct LuFS_master_block * master, struct virt_drv * drive)
{
    struct LuFS_data_block * last  = (struct LuFS_data_block *) drv_get_block(master->BP_FREE.NEXT_BLOCK_LBA48, drive);
    struct LuFS_data_block * first = (struct LuFS_data_block *) drv_get_block(last->BP_NEXT.NEXT_BLOCK_LBA48, drive);
    struct LuFS_data_block * p     = first;

    for (int i = 0; i < n - 1; i++) {
        p = (struct LuFS_data_block *) drv_get_block(p->BP_NEXT.NEXT_BLOCK_LBA48, drive);
    }
    struct LuFS_block_pointer tmp = last->BP_NEXT;
    last->BP_NEXT = p->BP_NEXT;
    p->BP_NEXT    = tmp;
    return (struct LuFS_block *) first;
}
