#ifndef DISK_H
#define DISK_H
#include <stdbool.h>
#include <stdint.h>
#include "ATA/ata.h"
#include "drive.h"

bool sect_read(uint32_t drive, uint64_t adress, uint8_t * buf);
bool sect_write(uint32_t drive, uint64_t adress, uint8_t * buf);
bool drive_discover();

struct Drive drives[32];

#endif // ifndef DISK_H
