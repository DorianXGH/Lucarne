#include "../port.h"
#include "../../util.h"
#include <stdint.h>

uint16_t ATA_PIO_bl_common(uint16_t drive, uint64_t numblock, uint16_t count);
uint16_t ATA_PIO_bl_read(uint16_t drive, uint64_t numblock, uint16_t count, char * buf);
uint16_t ATA_PIO_bl_write(uint16_t drive, uint64_t numblock, uint16_t count, char * buf);
