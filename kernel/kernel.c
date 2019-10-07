#include "drivers/keyboard.h"
#include "drivers/screen.h"
#include "drivers/timer.h"
#include "isr.h"
#include "memory/memory_segment.h"
#include "shell/shell.h"
#include "memory/page_allocator.h"
#include "memory/pdt.h"
#include "memory/pt.h"

extern struct def_vga_screen default_screen;
extern struct def_shell default_shell;
extern struct memory_seg_des * memmap;
extern int * nummem;
extern int max_page;
extern int last_inserted_page;


void _start()
{
    if (1) {
        memmap = (struct memory_seg_des *) 0x9104;
        nummem = (int *) 0x9100;
        last_inserted_page = 0;


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
        init_page_alloc();
        for (int i = 0; i < 50; i++) {
            preserve(i);
        }
        find_next_free();
        int gp_dir_page = palloc();
        void * general_page_directory = (void *) (gp_dir_page * 0x1000);
        // int page_table_page = palloc();
        init_pdt(general_page_directory);
        // struct pte * page_table = (struct pte *) (page_table_page * 0x1000);
        // for (int i = 0; i < 1024; i++) {
        //     struct pte entry;
        //     entry.accessed         = 0;
        //     entry.sysinfo          = 1;
        //     entry.dirty            = 0;
        //     entry.user             = 0;
        //     entry.write            = 1;
        //     entry.reserved2        = 0;
        //     entry.reserved         = 0;
        //     entry.present          = 1;
        //     entry.physical_address = i;
        //     page_table[i]          = entry;
        // }
        // struct pde entry;
        // entry.accessed           = 0;
        // entry.size               = 0;
        // entry.cache_disabled     = 0;
        // entry.sysinfo            = 1;
        // entry.user               = 0;
        // entry.write              = 1;
        // entry.present            = 1;
        // entry.global             = 0;
        // entry.wrtie_through      = 0;
        // entry.page_table_address = page_table_page;
        // ((struct pde *) general_page_directory)[0] = entry;
        identity_page(general_page_directory, min(0x10000, max_page));
        load_pdt(general_page_directory);
        putchar(&default_screen, '%');
        // enable_paging();
    }
} /* _start */
