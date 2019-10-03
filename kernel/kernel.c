#include "drivers/keyboard.h"
#include "drivers/screen.h"
#include "drivers/timer.h"
#include "isr.h"
#include "memory/memory_segment.h"
#include "shell/shell.h"

extern struct def_vga_screen default_screen;
extern struct def_shell default_shell;
extern struct memory_seg_des *memmap;

void dummy_test_entrypoint() {}
void main() {
  if (1) {
    memmap = (struct memory_seg_des *)0x9104;
    long int * nummem = (long int*)0x9100;
    default_screen.width = 80;
    default_screen.height = 25;
    default_screen.cursorx = 0;
    default_screen.cursory = 0;
    clear(&default_screen);

    putstring(&default_screen, "Loading IDT\n");
    isr_install();
    putstring(&default_screen, "IDT Loaded\n");
    putstring(&default_screen, "Loading Shell\n");

    default_shell.appointed_screen = &default_screen;
    for (int i = 0; i < 256; i++) {
      default_shell.current_input[i] = 0;
    }
    default_shell.current_index = 0;
    putstring(&default_screen, "Shell Loaded\n");
    putstring(&default_screen, "Initializing Keyboard\n");

    asm volatile("sti");
    // init_timer(10);
    /* Comment out the timer IRQ handler to read
     * the keyboard IRQs easier */
    init_keyboard();
    putstring(&default_screen, "Keyboard Loaded\n");
    clear(&default_screen);
    shell_invite(&default_shell);
    char base[16];
    char len[16];

    prntnum(memmap->base, 16, '+', base, 16);
    prntnum(memmap->length, 16, '+', len, 16);
    putstring(&default_screen, base);
    putchar(&default_screen, '|');
    putstring(&default_screen, len);
    putchar(&default_screen, ':');
    char numstr[16];
    for(int i = 0; i < 24; i++)
    {
        prntnum((long int)*(nummem+4+8*i), 16, '+', numstr, 16);
        putstring(&default_screen, numstr);
    }
  }
}
