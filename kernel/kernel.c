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
#include "cpuid/cpuid.h"

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
    struct gdt * edt = GDT_PTR_ADDR; // pointer to where the GDT Descriptor will be

    edt->base = GDT_ADDR;                    // put the adress of the GDT in it
    edt->size = 0xFFFF;                      // 0-1 = 2 complement : size of GDT is always 1 less than it should. Why ? ask intel
    add_to_gdt(edt, 0, 0, 0, NULL, 0);       // null segment, needed because the first segment is ignored. Why ? ASK INTEL
    add_to_gdt(edt, 0, 0xFFFFF, 0, CODE, 1); // code segment spanning the whole memory
    add_to_gdt(edt, 0, 0xFFFFF, 0, DATA, 2); // same for data segment
    dt = *edt;                               // load the pointer to the gdt descriptor in the global pointer to pass it to assembly code

    // if we used Multiboot spec
    #ifdef MULTIB

    struct mb_info_block * mbblck_copy = (struct mb_info_block *) MB_BLCK_ADDR; // copy the info block to the inteded loacation to prevent overwriting it
    *mbblck_copy = *mbblck;

    #endif

    memmap = (struct memory_seg_des *) MMAP_PTR; // load the correct locations
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

    uint32_t ecx, edx;
    cpuid_get_features(&ecx, &edx);
    if (edx & CPUID_FEAT_EDX_SSE) {
        cpuid_enable_sse();
    }
    // load screen data from info block
    // TODO : Multiboot sanity
    default_screen.width        = mbblck_copy->framebuffer_width;
    default_screen.height       = mbblck_copy->framebuffer_height;
    default_screen.pitch        = mbblck_copy->framebuffer_pitch;
    default_screen.bpp          = mbblck_copy->framebuffer_bytesperpixel;
    default_screen.cursorx      = 0;
    default_screen.cursory      = 0;
    default_screen.type         = VESA;
    default_screen.video_memory = (char *) (mbblck_copy->framebuffer_addr);

    clear(&default_screen); // clear the screen


    // init_timer(10);

    // Paging initialisation part
    last_inserted_page = 0;                // allow Fast ID paging by storing the last index inserted
    page_tracker       = PAGETRACKER_ADDR; // set the page tracker where it's supposed to be
    init_page_alloc();                     // init the tracker and allocator by allowing allocation on usable memory
    putstring(&default_screen, "Init page allocator\n");
    for (int i = 0; i < 0x0500; i++) { // reserve mory for kernel code
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
    find_next_free(); // find first allocatable page
    putstring(&default_screen, "Enabled page allocator\n");


    int gp_dir_page = palloc();
    void * general_page_directory = (void *) (gp_dir_page * 0x1000); // finding a page to store de PDT

    init_pdt(general_page_directory); // initialise the PDT
    putstring(&default_screen, "Starting ID Paging");
    fast_identity_page(general_page_directory, min(1024 * 1024, max_page)); // id page
    putstring(&default_screen, "ID Paged");
    load_pdt(general_page_directory); // load the PDT
    putstring(&default_screen, "Loaded PDT");

    enable_paging(); // enable paging (duh)

    clear(&default_screen);
    putstring(&default_screen, "Paging enabled");
    putchar(&default_screen, '\n');
    init_keyboard(); // initialise keyboard driver


    ft_basic_install(); // load the basic font


    struct def_vga_screen virt_scr = default_screen;                                                         // double bufffering
    virt_scr.bpp = 32;                                                                                       // enable alpha channel
    uint32_t * virt_frb = (uint32_t *) (palloc_n(((virt_scr.width * virt_scr.height) / 1024) + 1) * 0x1000); // allocate video memory
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
            putpixel_32(&virt_scr, c, x, y); // write weird things on the screen
        }
    }

    // draw a black rectangle on the screen
    uint32_t numpix      = (virt_scr.width - 50) * (virt_scr.height - 50);        // number of pixels
    uint32_t * testalpha = (uint32_t *) (palloc_n((numpix / 1024) + 1) * 0x1000); // allocate necessary memory
    char ptrstr[16];
    prntnum((uint32_t) testalpha, ' ', ptrstr, 16); // where was it put in memory ?


    struct sprite talpha; // data on the sprite
    talpha.bpp    = 32;
    talpha.height = virt_scr.height - 50;
    talpha.width  = virt_scr.width - 50;
    talpha.pixels = (uint8_t *) testalpha;

    for (int r = 0; r < numpix; r++) {
        int y = r / talpha.width - 350;
        int x = r % talpha.width - 500;
        if (x * x + y * y <= 100000 || 1) testalpha[r] = 0xFF000000;  // write black
    }

    putsprite(&virt_scr, &talpha, 25, 25); // put in on the buffer


    for (int k = 0; k < 10 && ptrstr[k] != '\0'; k++) {
        ft_print_char(&virt_scr, &ft_basic, ptrstr[k], 2 + k * 8, 2, 0xFFFFFF); // display where the rectable is in memory
    }


    helloworld(&virt_scr); // write helloworld

    set_screen_alpha(&virt_scr, 0xFF);      // set the virtual screen at 100% opacity;
    blit(&virt_scr, &default_screen, 0, 0); // blit the virtual screen on the real screen

    struct def_vga_screen terminal_screen;

    int margin = 40;


    terminal_screen.width        = ((virt_scr.width - 2 * margin) / (ft_basic.charwidth + ft_basic.interchar_x));
    terminal_screen.height       = ((virt_scr.height - 2 * margin) / (ft_basic.charheight + ft_basic.interchar_y));
    terminal_screen.pitch        = 2 * terminal_screen.width;
    terminal_screen.bpp          = 16;
    terminal_screen.cursorx      = 0;
    terminal_screen.cursory      = 0;
    terminal_screen.type         = TEXT;
    terminal_screen.video_memory = (char *) (palloc_n(4) * 0x1000);

    default_shell.appointed_screen = &terminal_screen;
    default_shell.font       = &ft_basic;
    default_shell.term_color = 0xFFFFFF;
    for (int i = 0; i < 256; i++) {
        default_shell.current_input[i] = 0;
    }
    default_shell.current_index = 0;

    // Interrupts enable
    asm volatile ("sti");
    putstring(&default_screen, "Interrupts restart\n");

    putstring(&terminal_screen, "Shell Loaded, awaiting instructions. <Lucarne's Kernel:\"beta\"> \n");
    shell_invite(&default_shell);
    int azer = 0;
    while (1) {
        putsprite(&virt_scr, &talpha, 25, 25); // put in on the buffer
        blit_shell(&default_shell, &virt_scr, margin, margin);
        putpixel(&virt_scr, 0x00FF00, azer % virt_scr.width, 26);
        putpixel(&virt_scr, 0x00FF00, azer % virt_scr.width, 27);
        putpixel(&virt_scr, 0x00FF00, azer % virt_scr.width, 28);
        putpixel(&virt_scr, 0x00FF00, (azer + 1) % virt_scr.width, 26);
        putpixel(&virt_scr, 0x00FF00, (azer + 1) % virt_scr.width, 27);
        putpixel(&virt_scr, 0x00FF00, (azer + 1) % virt_scr.width, 28);
        putpixel(&virt_scr, 0x00FF00, (azer + 2) % virt_scr.width, 26);
        putpixel(&virt_scr, 0x00FF00, (azer + 2) % virt_scr.width, 27);
        putpixel(&virt_scr, 0x00FF00, (azer + 2) % virt_scr.width, 28);
        // set_screen_alpha(&virt_scr, 0xFF);
        screencopy(&virt_scr, &default_screen);
        for (int k = 0; k < 1000; k++) { }
        azer++;
    }
} /* _start */
