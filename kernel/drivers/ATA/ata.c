#include "ata.h"

bool ATA_sect_read(uint32_t drive, uint64_t adress, uint8_t * buf)
{
    struct ATA_drive d = ATA_drives[drive % 32];

    switch (d.mode) {
        case PIO:
            ATA_PIO_bl_read(d.slave, adress, 1, buf, d.LBA48);
            break;

        default:
            break;
    }
    return true;
}

bool ATA_sect_write(uint32_t drive, uint64_t adress, uint8_t * buf)
{
    struct ATA_drive d = ATA_drives[drive % 32];

    switch (d.mode) {
        case PIO:
            ATA_PIO_bl_write(d.slave, adress, 1, buf, d.LBA48);
            break;

        default:
            break;
    }
    return true;
}

bool ATA_drive_discover()
{
    return true;
}
