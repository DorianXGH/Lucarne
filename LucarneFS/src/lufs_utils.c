#include "../headers/lufs_utils.h"
#include "../headers/lucarnefs.h"
#include "../headers/tests.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

uint64_t drv_get_last_LBA(FILE * drive)
{
    fseek(drive, 0L, SEEK_END);
    uint64_t sz = ftell(drive);
    return sz >> 9; // (divide by 512)
}

struct LuFS_block * drv_get_block(uint64_t LBA48, FILE * drive)
{
    if (LBA48 < drv_get_last_LBA(drive)) {
        fseek(drive, LBA48 * 512, SEEK_SET);
        struct LuFS_block * blck = (struct LuFS_block *) malloc(sizeof(struct LuFS_block));
        fread(blck, sizeof(struct LuFS_block), 1, drive);
        return blck;
    } else {
        printf("ERROR : tried to access not present LBA");
    }
}
