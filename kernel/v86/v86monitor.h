#ifndef V86MONITOR_H
#define V86MONITOR_H
#include <stdint.h>
extern void entering_v86(uint32_t ss, uint32_t esp, uint32_t cs, uint32_t eip);
extern void interrupt_10_v86(uint16_t ss, uint16_t esp, uint16_t cs, uint16_t eip);

#endif
