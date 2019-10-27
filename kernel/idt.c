#include "idt.h"
#include "util.h"

void set_idt_gate(uint32_t n, uint32_t handler)
{
    idt[n].low_offset  = low_16(handler);
    idt[n].sel         = KERNEL_CS;
    idt[n].null        = 0;
    idt[n].gatetype    = 0xE; // interrupt gate
    idt[n].storage     = 0;
    idt[n].ring        = 0; // kernel interrupt
    idt[n].present     = 1; // kernel interrupt
    idt[n].high_offset = high_16(handler);
}

void set_idt()
{
    idt_reg.base  = (int) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    /* Don't make the mistake of loading &idt -- always load &idt_reg */
    __asm__ __volatile__ ("lidtl (%0)" : : "r" (&idt_reg));
}
