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
#include "fonts/font_desc.h"
#include "fonts/font_basic.h"

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
extern struct font_desc ft_basic;

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
        if (1) {
            default_screen.width        = mbblck_copy->framebuffer_width;
            default_screen.height       = mbblck_copy->framebuffer_height;
            default_screen.pitch        = mbblck_copy->framebuffer_pitch;
            default_screen.bpp          = mbblck_copy->framebuffer_bytesperpixel;
            default_screen.cursorx      = 0;
            default_screen.cursory      = 0;
            default_screen.type         = VESA;
            default_screen.video_memory = (char *) (mbblck_copy->framebuffer_addr);
        }
        struct def_vga_screen double_buffer = default_screen;
        double_buffer.bpp = 32;

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
            fast_identity_page(general_page_directory, min(1024 * 1024, max_page));
            putstring(&default_screen, "ID Paged");
            load_pdt(general_page_directory);
            putstring(&default_screen, "Loaded PDT");

            enable_paging();

            clear(&default_screen);
            putstring(&default_screen, "Paging enabled");
            putchar(&default_screen, '\n');
            init_keyboard();

            shell_invite(&default_shell);
        }
        if (mbblck->flags & (1 << 12) && 1) {
            // default_screen.video_memory[4] = 250;
            char framebuffer_addr[10];
            char framebuffer_type[10];
            char framebuffer_width[10];
            char framebuffer_height[10];
            char framebuffer_bpp[10];
            prntnum(mbblck_copy->framebuffer_addr, ' ', framebuffer_addr, 10);
            prntnum(mbblck_copy->framebuffer_type, ' ', framebuffer_type, 10);
            prntnum(mbblck_copy->framebuffer_width, ' ', framebuffer_width, 10);
            prntnum(mbblck_copy->framebuffer_height, ' ', framebuffer_height, 10);
            prntnum(mbblck_copy->framebuffer_bytesperpixel, ' ', framebuffer_bpp, 10);
            putstring(&default_screen, framebuffer_addr);
            putstring(&default_screen, "\n");
            putstring(&default_screen, framebuffer_type);
            putstring(&default_screen, "\n");
            putstring(&default_screen, framebuffer_width);
            putstring(&default_screen, "\n");
            putstring(&default_screen, framebuffer_height);
            putstring(&default_screen, "\n");
            putstring(&default_screen, framebuffer_bpp);
            putstring(&default_screen, "\n");
        }
        // for (int x = 50; x < 250; x++) {
        //     for (int y = 50; y < 150; y++) {
        //         putpixel(&default_screen, 10, x, y);
        //     }
        // }
        if (1) {
            int rs = 10000;
            int x0 = default_screen.width / 2;
            int y0 = default_screen.height / 2;
            if (1) {
                for (int x = 0; x < default_screen.width; x++) {
                    for (int y = 0; y < default_screen.height; y++) {
                        int ns = (x - x0) * (x - x0) + (y - y0) * (y - y0);
                        ns /= 3;
                        struct color_32 c;
                        c.r = ns / 50;
                        c.g = 255 / (ns + 1);
                        c.b = 255 - ns / 50;
                        putpixel_32(&default_screen, c, x, y);
                    }
                }
                int numpix = (default_screen.width - 50) * (default_screen.height - 50);
                uint32_t * testalpha = (uint32_t *) (palloc() * 0x1000);

                for (int r = 0; r < numpix; r++) {
                    testalpha[r] = 0xFF000000;
                }

                struct sprite talpha;
                talpha.bpp    = 32;
                talpha.height = default_screen.height - 50;
                talpha.width  = default_screen.width - 50;
                talpha.pixels = (uint8_t *) testalpha;
                putsprite(&default_screen, &talpha, 25, 25);

                ft_basic_install();

                ft_print_char(&default_screen, &ft_basic, 'a', 30, 30, 0xFF00FF);
                ft_print_char(&default_screen, &ft_basic, 'b', 38, 30, 0xFFFFFF);
                ft_print_char(&default_screen, &ft_basic, 'q', 46, 30, 0xFFFFFF);
                ft_print_char(&default_screen, &ft_basic, 'w', 30, 42, 0xFFFFFF);
                ft_print_char(&default_screen, &ft_basic, 'w', 38, 42, 0xFFFFFF);
                ft_print_char(&default_screen, &ft_basic, 'w', 46, 42, 0xFFFFFF);
            }
        }
    }
} /* _start */
