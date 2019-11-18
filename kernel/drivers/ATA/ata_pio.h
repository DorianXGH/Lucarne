#include "../port.h"
#include "../../util.h"
#include <stdint.h>
#include <stdbool.h>

uint16_t ATA_PIO_bl_common(uint16_t drive, uint64_t numblock, uint16_t count, bool);
uint16_t ATA_PIO_bl_read(uint16_t drive, uint64_t numblock, uint16_t count, char * buf, bool);
uint16_t ATA_PIO_bl_write(uint16_t drive, uint64_t numblock, uint16_t count, char * buf, bool);
uint16_t ATA_PIO_IDENTITY(uint16_t drive, uint8_t * buf);
