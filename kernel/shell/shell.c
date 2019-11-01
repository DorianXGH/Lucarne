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
    } else if (sh->current_index < 128) {
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
    if (strcompare(sh->current_input, "CPUID")) {
        print_cpuid(sh->appointed_screen);
    }
    putchar(sh->appointed_screen, '\n');
}

void shell_invite(struct def_shell * sh)
{
    putchar(sh->appointed_screen, '>');
}
