#include "disk.h"
bool sect_read(uint32_t drive, uint64_t adress, uint8_t * buf)
{
    struct Drive d = drives[drive % 32];

    switch (d.protocol) {
        case ATA:
            ATA_sect_read(d.pr_id, adress, buf);
            break;

        default:

            break;
    }
    return true;
}

bool sect_write(uint32_t drive, uint64_t adress, uint8_t * buf)
{
    struct Drive d = drives[drive % 32];

    switch (d.protocol) {
        case ATA:
            ATA_sect_write(d.pr_id, adress, buf);
            break;

        default:

            break;
    }
    return true;
}

bool drive_discover()
{
    ATA_drive_discover();
    return true;
}
