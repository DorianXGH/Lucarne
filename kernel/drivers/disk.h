#ifndef DISK_H
#define DISK_H
#include <stdbool.h>
#include <stdint.h>

enum Drive_Protocol {
    ATA,
    AHCI
};

struct Drive {
    enum Drive_Protocol protocol;
    uint32_t            pr_id;
};
bool sect_read(uint32_t drive, uint64_t adress, uint8_t * buf);
bool sect_write(uint32_t drive, uint64_t adress, uint8_t * buf);

#endif // ifndef DISK_H
