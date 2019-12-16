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
    uint64_t                      NEXT_BLOCK_LBA48 : 48;
} __attribute__((packed));

struct LuFS_master_block {
    uint8_t                       SIGNATURE[4];
    uint8_t                       FS_VERSION;
    uint8_t                       FLAGS;
    struct LuFS_volume_identifier VOLUME_ID;
    struct LuFS_volume_identifier SLAVE_VOLUMES[64];
    uint8_t                       RESERVED[328];
    struct LuFS_block_pointer     BP_CURRENT_OP;
    struct LuFS_block_pointer     BP_FREE;
    struct LuFS_block_pointer     BP_ROOT;
} __attribute__((packed));

struct LuFS_folder_block {
    struct LuFS_block_pointer BP_NAME;
    uint8_t                   RESERVED[463];
    uint8_t                   FLAGS;
    struct LuFS_block_pointer BP_CONTENT;
    struct LuFS_block_pointer BP_NEXT;
} __attribute__((packed));

struct LuFS_file_block {
    struct LuFS_block_pointer BP_NAME;
    uint32_t                  LENGTH_IN_BYTES;
    uint8_t                   RESERVED[459];
    uint8_t                   FLAGS;
    struct LuFS_block_pointer BP_CONTENT;
    struct LuFS_block_pointer BP_NEXT;
} __attribute__((packed));

struct LuFS_data_block {
    uint8_t                   DATA[448];
    uint8_t                   RESERVED[48];
    struct LuFS_block_pointer BP_NEXT;
} __attribute__((packed));

#endif // ifndef LUCARNEFS_H
