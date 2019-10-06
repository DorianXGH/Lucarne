#include "drivers/keyboard.h"
#include "drivers/screen.h"
#include "drivers/timer.h"
#include "isr.h"
#include "memory/memory_segment.h"
#include "shell/shell.h"
#include "memory/page_allocator.h"
#include "memory/pdt.h"

extern struct def_vga_screen default_screen;
extern struct def_shell default_shell;
extern struct memory_seg_des * memmap;
extern int * nummem;
extern int max_page;

void _start()
{
    if (1) {
        memmap = (struct memory_seg_des *) 0x9104;
        nummem = (int *) 0x9100;


        putstring(&default_screen, "Loading IDT\n");
        isr_install();
        putstring(&default_screen, "IDT Loaded\n");
        putstring(&default_screen, "Loading Shell\n");

        default_screen.width   = 80;
        default_screen.height  = 25;
        default_screen.cursorx = 0;
        default_screen.cursory = 0;
        clear(&default_screen);
        int k = 0;

        init_page_alloc();
        for (int i = 0; i < 50; i++) {
            preserve(i);
        }

        /*
         * void * general_page_directory = (void *) (palloc() * 0x1000);
         * identity_page(general_page_directory, 0x10000);
         * load_pdt(general_page_directory);
         * enable_paging();
         * for (int i = 0; i < 0x1000000; i++) k++;
         */


        default_shell.appointed_screen = &default_screen;
        for (int i = 0; i < 256; i++) {
            default_shell.current_input[i] = 0;
        }
        default_shell.current_index = 0;
        putstring(&default_screen, "Shell Loaded\n");
        putstring(&default_screen, "Initializing Keyboard\n");

        asm volatile ("sti");
        // init_timer(10);

        /* Comment out the timer IRQ handler to read
         * the keyboard IRQs easier */
        init_keyboard();
        putstring(&default_screen, "Keyboard Loaded\n");
        clear(&default_screen);
        shell_invite(&default_shell);
        char num[10];
        prntnum(sizeof(struct pte), '+', num, 10);
        putstring(&default_screen, num);
    }
} /* _start */
