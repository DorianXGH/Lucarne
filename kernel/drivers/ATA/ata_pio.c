#include "ata_pio.h"
#include "../screen.h"
#include "../../fonts/font_desc.h"
#include "../../fonts/font_basic.h"

extern struct font_desc ft_basic;
uint16_t ATA_PIO_bl_common(uint16_t drive, uint64_t numblock, uint16_t count, bool LBA48)
{
    if (LBA48) {
        outb(0x1F6, 0x40 | (drive << 4));

        // for (int i = 0; i < 4; i++) inb(0x1F7);  // 400 ns delay TODO : sleep command
        // while (!(inb(0x1F7) & (1 << 7)));        // check BSY bit of status register

        outb(0x1F1, 0x00); /* NULL byte to port 0x1F1 */
        // consecutive outs to the same ports are bad
        outb(0x1F2, count && 0xFF);
        outb(0x1F3, numblock && 0xFF);
        outb(0x1F4, (numblock >> 8) && 0xFF);
        outb(0x1F5, (numblock >> 16) && 0xFF);

        outb(0x1F2, count >> 8);
        outb(0x1F3, (numblock >> 24) && 0xFF);
        outb(0x1F4, (numblock >> 32) && 0xFF);
        outb(0x1F5, (numblock >> 40) && 0xFF);
    } else {
        /* Drive indicator, magic bits, and highest 4 bits of the block address */
        outb(0x1F6, 0xE0 | (drive << 4) | ((numblock >> 24) & 0x0F));

        // for (int i = 0; i < 4; i++) inb(0x1F7);  // 400 ns delay TODO : sleep command
        // while (!(inb(0x1F7) & (1 << 7)));        // check BSY bit of status register

        outb(0x1F1, 0x00);                       /* NULL byte to port 0x1F1 */
        outb(0x1F2, count & 0xFF);               /* Sector count */
        outb(0x1F3, (uint8_t) numblock);         /* Low 8 bits of the block address */
        outb(0x1F4, (uint8_t) (numblock >> 8));  /* Next 8 bits of the block address */
        outb(0x1F5, (uint8_t) (numblock >> 16)); /* Next 8 bits of the block address */
    }
    return 0;
} /* bl_common */

uint16_t ATA_PIO_bl_read(uint16_t drive, uint64_t numblock, uint16_t count, char * buf, bool LBA48)
{
    uint16_t tmpword;
    uint32_t idx;

    ft_print_char(&default_screen, &ft_basic, '0', 400, 100, 0xFFFFFF);
    ATA_PIO_bl_common(drive, numblock, count, LBA48);

    outb(0x1F7, 0x20 | (LBA48) ? 0x4 : 0);

    ft_print_char(&default_screen, &ft_basic, '1', 410, 100, 0xFFFFFF);

    /* Wait for the drive to signal that it's ready: */
    while (!(inb(0x1F7) & 0x08));

    ft_print_char(&default_screen, &ft_basic, '2', 420, 100, 0xFFFFFF);

    for (idx = 0; idx < 256 * count; idx++) {
        tmpword          = inw(0x1F0);
        buf[idx * 2]     = (uint8_t) tmpword;
        buf[idx * 2 + 1] = (uint8_t) (tmpword >> 8);
    }
    ft_print_char(&default_screen, &ft_basic, '3', 430, 100, 0xFFFFFF);
    return count;
}

uint16_t ATA_PIO_bl_write(uint16_t drive, uint64_t numblock, uint16_t count, char * buf, bool LBA48)
{
    uint16_t tmpword;
    uint32_t idx;

    ATA_PIO_bl_common(drive, numblock, count, LBA48);
    outb(0x1F7, 0x30 | (LBA48) ? 0x4 : 0);

    /* Wait for the drive to signal that it's ready: */
    while (!(inb(0x1F7) & 0x08));

    for (idx = 0; idx < 256 * count; idx++) {
        tmpword = (buf[idx * 2 + 1] << 8) | buf[idx * 2];
        outw(0x1F0, tmpword);
    }

    // cache flush
    outb(0x1F7, 0xE7);
    for (int i = 0; i < 4; i++) inb(0x1F7);  // 400 ns delay TODO : sleep command
    while (!(inb(0x1F7) & (1 << 7)));        // check BSY bit of status register

    return count;
}
