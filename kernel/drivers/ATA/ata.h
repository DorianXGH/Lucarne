#ifndef ATA_H
#define ATA_H
#include <stdbool.h>
#include <stdint.h>

enum ATA_mode {
    PIO,
    DMA
};

struct ATA_drive {
    bool     slave;
    ATA_mode mode;
};

bool ATA_sect_read(uint32_t drive, uint64_t adress, uint8_t * buf);
bool ATA_sect_write(uint32_t drive, uint64_t adress, uint8_t * buf);

ATA_drive ATA_drives[32];


#endif // ifndef ATA_H
