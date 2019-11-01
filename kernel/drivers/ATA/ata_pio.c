#include "ata_pio.h"
uint16_t bl_common(uint16_t drive, uint64_t numblock, uint16_t count, bool LBA48)
{
    if (LBA48) {
        outb(0x1F1, 0x00);       /* NULL byte to port 0x1F1 */
        outb(0x1F2, count >> 8); /* Sector count */
        outb(0x1F2, count && 0xFF);
        outb(0x1F3, (uint8_t) (numblock >> 24));
        outb(0x1F3, (uint8_t) numblock);
        outb(0x1F4, (uint8_t) (numblock >> 32));
        outb(0x1F4, (uint8_t) (numblock >> 8));
        outb(0x1F5, (uint8_t) (numblock >> 40));
        outb(0x1F5, (uint8_t) (numblock >> 16));
        outb(0x1F6, 0x40 | (drive << 4));
    } else {
        outb(0x1F1, 0x00);                       /* NULL byte to port 0x1F1 */
        outb(0x1F2, count & 0xFF);               /* Sector count */
        outb(0x1F3, (uint8_t) numblock);         /* Low 8 bits of the block address */
        outb(0x1F4, (uint8_t) (numblock >> 8));  /* Next 8 bits of the block address */
        outb(0x1F5, (uint8_t) (numblock >> 16)); /* Next 8 bits of the block address */

        /* Drive indicator, magic bits, and highest 4 bits of the block address */
        outb(0x1F6, 0xE0 | (drive << 4) | ((numblock >> 24) & 0x0F));
    }
    return 0;
}

uint16_t bl_read(uint16_t drive, uint64_t numblock, uint16_t count, char * buf, bool LBA48)
{
    uint16_t tmpword;
    uint32_t idx;

    bl_common(drive, numblock, count, LBA48);
    outb(0x1F7, 0x20 | (LBA48) ? 0x4 : 0);

    /* Wait for the drive to signal that it's ready: */
    while (!(inb(0x1F7) & 0x08));

    for (idx = 0; idx < 256 * count; idx++) {
        tmpword          = inw(0x1F0);
        buf[idx * 2]     = (uint8_t) tmpword;
        buf[idx * 2 + 1] = (uint8_t) (tmpword >> 8);
    }

    return count;
}

uint16_t bl_write(uint16_t drive, uint64_t numblock, uint16_t count, char * buf, bool LBA48)
{
    uint16_t tmpword;
    uint32_t idx;

    bl_common(drive, numblock, count, LBA48);
    outb(0x1F7, 0x30 | (LBA48) ? 0x4 : 0);

    /* Wait for the drive to signal that it's ready: */
    while (!(inb(0x1F7) & 0x08));

    for (idx = 0; idx < 256 * count; idx++) {
        tmpword = (buf[idx * 2 + 1] << 8) | buf[idx * 2];
        outw(0x1F0, tmpword);
    }

    return count;
}
