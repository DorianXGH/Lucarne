#include "drivers/keyboard.h"
#include "drivers/screen.h"
#include "drivers/timer.h"
#include "isr.h"
#include "memory/memory_segment.h"
#include "shell/shell.h"
#include "memory/page_allocator.h"
#include "memory/pdt.h"
#include "memory/pt.h"
#include "memory/gdt.h"
#include "multiboot/mb_info_block.h"

#define MULTIB
#ifdef MULTIB
# define GDT_PTR_ADDR 0x00400000
# define GDT_ADDR     0x00401000
# define MMAP_PTR     0x00211000
# define MMAP_LEN_PTR 0x00210000
# define MB_BLCK_ADDR 0x00200000
#endif
#ifndef MULTIB
# define GDT_PTR_ADDR 0x9450
# define GDT_ADDR     0x9500
# define MMAP_PTR     0x9104
# define MMAP_LEN_PTR 0x9100

#endif


extern struct def_vga_screen default_screen;
extern struct def_shell default_shell;
extern struct memory_seg_des * memmap;
extern int * nummem;
extern int max_page;
extern int last_inserted_page;
extern struct gdt dt;

void _start(struct mb_info_block * mbblck)
{
    if (1) {
        struct gdt * edt = GDT_PTR_ADDR;
        edt->base = GDT_ADDR;
        edt->size = 0xFFFF; // 0-1 = 2 complement
        add_to_gdt(edt, 0, 0, 0, NULL, 0);
        add_to_gdt(edt, 0, 0xFFFFF, 0, CODE, 1);
        add_to_gdt(edt, 0, 0xFFFFF, 0, DATA, 2);
        dt = *edt;
        #ifdef MULTIB
        struct mb_info_block * mbblck_copy = (struct mb_info_block *) MB_BLCK_ADDR;
        *mbblck_copy = *mbblck;

        #endif

        memmap = (struct memory_seg_des *) MMAP_PTR;
        nummem = (int *) MMAP_LEN_PTR;

        #ifdef MULTIB
        if (mbblck->mmap_length > 0 && (mbblck->flags & 0x00000040)) {
            struct memory_seg_des * mmap = mbblck->mmap_addr;

            int ind = 0;
            while ((int) mmap < mbblck->mmap_addr + mbblck->mmap_length) {
                memmap[ind] = *mmap;
                mmap        = (struct memory_seg_des *) ( (unsigned int) mmap + mmap->size + 4 );
                ind++;
            }
            *nummem = ind;
        }
        #endif /* ifdef MULTIB */

        last_inserted_page = 0;

        isr_install();
        load_gdt();


        default_screen.width        = 80;
        default_screen.height       = 25;
        default_screen.cursorx      = 0;
        default_screen.cursory      = 0;
        default_screen.type         = TEXT;
        default_screen.video_memory = (char *) 0xB8000;

        if (0) {
            default_screen.width        = 320;
            default_screen.height       = 200;
            default_screen.cursorx      = 0;
            default_screen.cursory      = 0;
            default_screen.type         = GRAPHIC;
            default_screen.video_memory = (char *) 0xA0000;
        }

        clear(&default_screen);
        int k = 0;
        #ifdef MULTIB
        putstring(&default_screen, "Multib\n");
        if (mbblck->mmap_length > 0 && (mbblck->flags & 0x00000040)) {
            putstring(&default_screen, "Mem map initialized\n");
        }
        #endif

        default_shell.appointed_screen = &default_screen;
        for (int i = 0; i < 256; i++) {
            default_shell.current_input[i] = 0;
        }
        default_shell.current_index = 0;
        putstring(&default_screen, "Shell Loaded\n");
        putstring(&default_screen, "Initializing Keyboard\n");

        asm volatile ("sti");
        putstring(&default_screen, "Interrupts restart\n");
        // init_timer(10);

        if (1) {
            init_page_alloc();
            putstring(&default_screen, "Init page allocator\n");
            for (int i = 0; i < 0x00500; i++) {
                preserve(i);
            }
            find_next_free();
            putstring(&default_screen, "Enabled page allocator\n");


            int gp_dir_page = palloc();
            void * general_page_directory = (void *) (gp_dir_page * 0x1000);

            init_pdt(general_page_directory);
            putstring(&default_screen, "Starting ID Paging");
            fast_identity_page(general_page_directory, min(0x10000, max_page));
            load_pdt(general_page_directory);
            putstring(&default_screen, "Loaded PDT");

            enable_paging();

            clear(&default_screen);
            putstring(&default_screen, "Paging enabled");
            putchar(&default_screen, '\n');
            init_keyboard();

            shell_invite(&default_shell);
        }
        // for (int x = 50; x < 250; x++) {
        //     for (int y = 50; y < 150; y++) {
        //         putpixel(&default_screen, 10, x, y);
        //     }
        // }
    }
} /* _start */
