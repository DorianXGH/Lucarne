#include "timer.h"
#include "screen.h"
#include "../util.h"
#include "../isr.h"
#include "port.h"

extern struct def_vga_screen default_screen;

int tick = 0;

static void timer_callback(registers_t regs)
{
    tick++;
    putstring(&default_screen, "Tick: ");

    char tick_ascii[256];
    int_to_ascii(tick, tick_ascii);
    putstring(&default_screen, tick_ascii);
    putstring(&default_screen, "\n");
}

void init_timer(int freq)
{
    /* Install the function we just wrote */
    register_interrupt_handler(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    int divisor = 1193180 / freq;
    char low    = (char) (divisor & 0xFF);
    char high   = (char) ( (divisor >> 8) & 0xFF);
    /* Send the command */
    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}
