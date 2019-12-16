#ifndef LUCARNEFS_H
#define LUCARNEFS_H
#include <stdint.h>

struct LuFS_volume_identifier {
    uint8_t DISK_GUID : 4;
    uint8_t PART_GUID : 8;
    uint8_t COLLISION_GUARD : 4;
} __attribute__((packed));

struct LuFS_block_pointer {
    uint64_t                      NEXT_BLOCK_LBA48_DUPLICATE : 48;
    uint16_t                      METADATA;
    struct LuFS_volume_identifier VOLUME_ID;
    uint64_t                      NEXT_BLOCK_LBA48_DUPLICATE : 48;
} __attribute__((packed));

struct LuFS_master_block {
    uint8_t                       SIGNATURE[4];
    uint8_t                       FS_VERSION;
    uint8_t                       FLAGS;
    struct LuFS_volume_identifier VOLUME_ID;
    struct LuFS_volume_identifier SLAVE_VOLUMES[64];
    uint8_t                       RESERVED[328];
    uint64_t                      NEXT_BLOCK_LBA48_DUPLICATE : 48;
} __attribute__((packed));

#endif // ifndef LUCARNEFS_H
