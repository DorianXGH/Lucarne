#ifndef ATA_H
#define ATA_H
#include <stdbool.h>
#include <stdint.h>
#include "../drive.h"
#include "../disk.h"
#include "ata_pio.h"

enum ATA_mode {
    PIO,
    DMA
};

struct ATA_drive {
    bool          slave;
    enum ATA_mode mode;
    bool          LBA48;
};

bool ATA_sect_read(uint32_t drive, uint64_t adress, uint8_t * buf);
bool ATA_sect_write(uint32_t drive, uint64_t adress, uint8_t * buf);
bool ATA_drive_discover();

struct ATA_drive ATA_drives[32];

extern struct Drive drives[32];


#endif // ifndef ATA_H
