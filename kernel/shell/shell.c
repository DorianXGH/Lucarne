#include "shell.h"
#include "../drivers/screen.h"
#include "../memory/memory_segment.h"
#include "../cpuid/cpuid.h"

void putchar_sh(struct def_shell * sh, char c)
{
    if (c == '\n') {
        putchar(sh->appointed_screen, c);
        shellexec(sh);
        sh->current_index = 0;
        for (int i = 0; i < 256; i++) {
            sh->current_input[i] = 0;
        }
        shell_invite(sh);
    } else if (sh->current_index < 255) {
        putchar(sh->appointed_screen, c);
        sh->current_input[sh->current_index] = c;
        sh->current_index++;
    }
}

void backspace(struct def_shell * sh)
{
    if (sh->current_index == 0) { } else {
        sh->current_index--;
        sh->current_input[sh->current_index] = 0;
        remove_char(sh->appointed_screen);
    }
}

void shellexec(struct def_shell * sh)
{
    putchar(sh->appointed_screen, '\n');
    if (strcompare(sh->current_input, "MEM")) {
        print_map(sh->appointed_screen);
    }
    else if (strcompare(sh->current_input, "CPUID")) {
        print_cpuid(sh->appointed_screen);
    }
    else if (strcompare(sh->current_input, "DREAD MASTER")) {
        char * k     = palloc_n(1) * 0x1000;
        uint16_t ret = ATA_PIO_bl_read(0, 0, 1, k, false);
        if (ret == 0) {
            putstring(sh->appointed_screen, "ERR\n");
            if (k[0] & 1) {
                putstring(sh->appointed_screen, "ADDRESS MARK NOT FOUND\n");
            }
            if (k[0] & (1 << 1)) {
                putstring(sh->appointed_screen, "TRACK 0 NOT FOUND\n");
            }
            if (k[0] & (1 << 2)) {
                putstring(sh->appointed_screen, "ABORTED COMMAND\n");
            }
            if (k[0] & (1 << 3)) {
                putstring(sh->appointed_screen, "MEDIA CHANGE REQUEST\n");
            }
            if (k[0] & (1 << 4)) {
                putstring(sh->appointed_screen, "ID NOT FOUND\n");
            }
            if (k[0] & (1 << 5)) {
                putstring(sh->appointed_screen, "MEDIA CHANGED\n");
            }
            if (k[0] & (1 << 6)) {
                putstring(sh->appointed_screen, "UNCORRECTABLE DATA ERR\n");
            }
            if (k[0] & (1 << 7)) {
                putstring(sh->appointed_screen, "BAD BLOCK\n");
            }
        }
        k[512] = 0;
        print_hex(sh->appointed_screen, k);
    }
    else if (strcompare(sh->current_input, "DREAD SLAVE")) {
        char * k = palloc_n(1) * 0x1000;
        ATA_PIO_bl_read(1, 0, 1, k, false);

        k[512] = 0;
        print_hex(sh->appointed_screen, k);
    }
    else if (strcompare(sh->current_input, "DID MASTER")) {
        char * k    = palloc_n(1) * 0x1000;
        uint16_t id = ATA_PIO_IDENTIFY(0, k);

        k[512] = 0;
        switch (id) {
            case 0:
                putstring(sh->appointed_screen, "NO DRIVE\n");
                break;
            case 1:
                putstring(sh->appointed_screen, "ERR SPEC\n");
                break;
            case 2:
                putstring(sh->appointed_screen, "ATAPI\n");
                break;
            case 3:
                putstring(sh->appointed_screen, "ATA ABORTED\n");
                break;
            case 4:
                putstring(sh->appointed_screen, "SATA\n");
                break;
            case 5:
                putstring(sh->appointed_screen, "ATA\n");
                print_hex(sh->appointed_screen, k);
                putstring(sh->appointed_screen, "\n");
                uint16_t * k2 = (uint16_t *) k;
                if (k2[83] & (1 << 10)) {
                    putstring(sh->appointed_screen, "LBA48 SUPPORTED\n");
                }
                uint32_t LBA24_count = k2[60] << 16 + k2[61];
                uint64_t LBA48_count = k2[100] << 48 + k2[101] << 32 + k2[102] << 16 + k2[103];
                char LBA24_count_buf[20];
                char LBA48_count_buf[40];
                prntnum(LBA24_count, ' ', LBA24_count_buf, 20);
                prntnum(LBA48_count, ' ', LBA48_count_buf, 40);
                putstring(sh->appointed_screen, "LBA24 sectors : \0");
                putstring(sh->appointed_screen, LBA24_count_buf);
                putstring(sh->appointed_screen, "\nLBA48 sectors : \0");
                putstring(sh->appointed_screen, LBA48_count_buf);
                putstring(sh->appointed_screen, "\n\0");
                break;
            case 6:
                putstring(sh->appointed_screen, "NO BUS\n");
                break;
            default:
                putstring(sh->appointed_screen, "UNKNOWN RETURN CODE\n");
                break;
        }
	}
	else if (strcompare(sh->current_input, "HELLOWORLD")) {
		putstring(sh->appointed_screen, "HELLO, WORLD!\n");
    }
	else if (strcompare(sh->current_input, "HALT")) {
		asm("hlt");
	}
	else if (strcompare(sh->current_input, "HELP")) {
		putstring(sh->appointed_screen, "LIST OF COMMANDS:\n\nMEM : PRINTS MEMORY MAP\nCPUID : SHOW CPU FEATURES\nDREAD MASTER : READS THE FIRST SECTOR OF MASTER DISK ON PRIMARY IDE BUS\nDREAD SLAVE : READS THE FIRST SECTOR OF SLAVE DISK ON PRIMARY IDE BUS\nDID MASTER : RETURNS THE RESULT OF \"ATA IDENTIFY\" ON PRIMARY DISK\nHELLOWORLD : PRINTS \"HELLO, WORLD!\"\nHALT : HALTS THE SYSTEM\nHELP : SHOWS THIS TEXT\n");

	}
	else {
		putstring(sh->appointed_screen, "UNKNOWN COMMAND. TYPE \"HELP\" FOR HELP.\n");
	}

    putchar(sh->appointed_screen, '\n');
} /* shellexec */

void shell_invite(struct def_shell * sh)
{
    putchar(sh->appointed_screen, '>');
}
