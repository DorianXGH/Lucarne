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
# define GDT_PTR_ADDR     0x00400000
# define GDT_ADDR         0x00401000
# define MMAP_PTR         0x00211000
# define MMAP_LEN_PTR     0x00210000
# define MB_BLCK_ADDR     0x00200000
# define PAGETRACKER_ADDR 0x00B00000
#endif
#ifndef MULTIB
# define GDT_PTR_ADDR 0x9450
# define GDT_ADDR     0x9500
# define MMAP_PTR     0x9104
# define MMAP_LEN_PTR 0x9100

#endif


extern struct def_vga_screen default_screen; // screen data
extern struct def_shell default_shell;       // shell data
extern struct memory_seg_des * memmap;       // where the memory map is
extern int * nummem;                         // numer of entires in the memory map
extern int max_page;                         // the number of pages in memory
extern int last_inserted_page;               // the last page inserted in the PDT : optimisation
extern struct gdt dt;                        // the GDT
extern struct font_desc ft_basic;            // the basic font data
extern uint8_t * page_tracker;               // where the page tracker is

void helloworld(struct def_vga_screen * virt_screen)
{
    char str[] = "hello world!   $  $    $$$   $$$$$";

    for (int i = 0; i < sizeof(str) / sizeof(char); i++) {
        ft_print_char(virt_screen, &ft_basic, str[i], 40 + 8 * i, 50, 0xEC15EF);
    }
}

void _start(struct mb_info_block * mbblck)
{
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
    if (mbblck->mmap_length > 0 && (mbblck->flags & 0x00000040)) { // if the bootloader gave the memmap info
        struct memory_seg_des * mmap = mbblck->mmap_addr;          // get the pointer to it

        int ind = 0;
        while ((int) mmap < mbblck->mmap_addr + mbblck->mmap_length) {                        // while there's stille something to copy
            memmap[ind] = *mmap;                                                              // copy
            mmap        = (struct memory_seg_des *) ( (unsigned int) mmap + mmap->size + 4 ); // move the pointer
            ind++;
        }
        *nummem = ind;
    }
    #endif /* ifdef MULTIB */

    // load Interrupts Descriptor Table
    isr_install();
    // load GDT and reload segment registers
    load_gdt();

    default_screen.width        = mbblck_copy->framebuffer_width;
    default_screen.height       = mbblck_copy->framebuffer_height;
    default_screen.pitch        = mbblck_copy->framebuffer_pitch;
    default_screen.bpp          = mbblck_copy->framebuffer_bytesperpixel;
    default_screen.cursorx      = 0;
    default_screen.cursory      = 0;
    default_screen.type         = VESA;
    default_screen.video_memory = (char *) (mbblck_copy->framebuffer_addr);

    struct def_vga_screen double_buffer = default_screen;
    double_buffer.bpp = 32;

    clear(&default_screen);


    // Interrupts enable
    asm volatile ("sti");
    putstring(&default_screen, "Interrupts restart\n");
    // init_timer(10);

    // Paging initialisation part
    last_inserted_page = 0;
    page_tracker       = PAGETRACKER_ADDR;
    init_page_alloc();
    putstring(&default_screen, "Init page allocator\n");
    for (int i = 0; i < 0x0500; i++) {
        preserve(i);
    }
    for (int i = PAGETRACKER_ADDR / 0x1000; i < ((PAGETRACKER_ADDR + (max_page / 8) ) / 0x1000) + 1; i++) { // reserve space for the page tracker
        preserve(i);
    }
    for (int i = (uint32_t) default_screen.video_memory / 0x1000; // reserve video mem
      i < ((uint32_t) default_screen.video_memory + default_screen.pitch * default_screen.width) / 0x1000 + 1;
      i++)
    {
        preserve(i);
    }
    find_next_free();
    putstring(&default_screen, "Enabled page allocator\n");


    int gp_dir_page = palloc();
    void * general_page_directory = (void *) (gp_dir_page * 0x1000); // finding a page to store de PDT

    init_pdt(general_page_directory);
    putstring(&default_screen, "Starting ID Paging");
    fast_identity_page(general_page_directory, min(1024 * 1024, max_page)); // id page
    putstring(&default_screen, "ID Paged");
    load_pdt(general_page_directory);
    putstring(&default_screen, "Loaded PDT");

    enable_paging();

    clear(&default_screen);
    putstring(&default_screen, "Paging enabled");
    putchar(&default_screen, '\n');
    init_keyboard();


    if (mbblck->flags & (1 << 12) && 1) { // if we are in VESA mode
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

    ft_basic_install();
    struct def_vga_screen virt_scr = default_screen;
    uint32_t * virt_frb = (uint32_t *) (palloc_n(((virt_scr.width * virt_scr.height) / 1024) + 1) * 0x1000);
    virt_scr.video_memory = virt_frb;


    int rs = 10000; // test of screen functions : destined to be deleted
    int x0 = virt_scr.width / 2;
    int y0 = virt_scr.height / 2;

    for (int x = 0; x < virt_scr.width; x++) {
        for (int y = 0; y < virt_scr.height; y++) {
            int ns = (x - x0) * (x - x0) + (y - y0) * (y - y0);
            ns /= 10;
            struct color_32 c;
            c.a = 0xFF;
            c.r = ns / 50;
            c.g = 255 / (ns + 1);
            c.b = 255 - ns / 50;
            putpixel_32(&virt_scr, c, x, y);
        }
    }
    uint32_t numpix      = (virt_scr.width - 50) * (virt_scr.height - 50);
    uint32_t * testalpha = (uint32_t *) (palloc_n((numpix / 1024) + 1) * 0x1000);
    char ptrstr[16];
    prntnum((uint32_t) testalpha, ' ', ptrstr, 16);


    struct sprite talpha;
    talpha.bpp    = 32;
    talpha.height = virt_scr.height - 50;
    talpha.width  = virt_scr.width - 50;
    talpha.pixels = (uint8_t *) testalpha;

    for (int r = 0; r < numpix; r++) {
        int y = r / talpha.width - 350;
        int x = r % talpha.width - 500;
        if (x * x + y * y <= 100000 || 1) testalpha[r] = 0xFF000000;
    }

    putsprite(&virt_scr, &talpha, 25, 25);


    for (int k = 0; k < 10 && ptrstr[k] != '\0'; k++) {
        ft_print_char(&virt_scr, &ft_basic, ptrstr[k], 2 + k * 8, 2, 0xFFFFFF);
    }


    helloworld(&virt_scr);

    set_screen_alpha(&virt_scr, 0xFF);
    blit(&virt_scr, &default_screen, 0, 0);

    default_shell.appointed_screen = &default_screen;
    for (int i = 0; i < 256; i++) {
        default_shell.current_input[i] = 0;
    }
    default_shell.current_index = 0;
    putstring(&default_screen, "Shell Loaded\n");
    shell_invite(&default_shell);
} /* _start */
