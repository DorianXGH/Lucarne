#ifndef GPT_H
#define GPT_H
#include <stdbool.h>
#include <stdint.h>
#include "../disk.h"

struct GPT_header {
    uint8_t  signature[8];
    uint8_t  version[4];
    uint32_t gpt_size;
    uint32_t header_CRC32;
    uint32_t reserved;
    uint64_t this_GPT_LBA;
    uint64_t other_GPT_LBA;
    uint64_t first_usable_LBA;
    uint64_t last_usable_LBA;
    uint8_t  disk_guid[16];
    uint64_t partition_table_LBA;
    uint32_t num_partitions;
    uint32_t descriptor_size;
    uint32_t table_CRC32;
} __attribute__((packed));

struct GPT_partition {
    uint8_t  type_GUID[16];
    uint8_t  partition_GUID[16];
    uint64_t first_LBA;
    uint64_t last_LBA;
    uint64_t flags;
    uint16_t name[36];
} __attribute__((packed));

#endif // ifndef GPT_H
