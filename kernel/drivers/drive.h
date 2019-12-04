#ifndef DRIVE_H
#define DRIVE_H

#include <stdint.h>
enum Drive_Protocol {
    ATA,
    AHCI
};

struct Drive {
    enum Drive_Protocol protocol;
    uint8_t             pr_id;
};

#endif // ifndef DRIVE_H
