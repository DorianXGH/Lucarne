#ifndef MB_INFO_BLOCK
#define MB_INFO_BLOCK
#include <stdint.h>

struct mb_info_block { // just go see the multiboot spec, it's really easy to understand
    uint32_t flags;
    uint32_t mem_low;
    uint32_t mem_high;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    uint32_t sym[4];
    uint32_t mmap_length;
    uint32_t mmap_addr;
    uint32_t drives_length;
    uint32_t drives_addr;
    uint32_t config_table;
    uint32_t boot_loader_name;
    uint32_t apm_table;
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t  framebuffer_bytesperpixel;
    uint8_t  framebuffer_type;
    uint16_t color_info[6];
} __attribute__((packed));

#endif /* ifndef MB_INFO_BLOCK */
