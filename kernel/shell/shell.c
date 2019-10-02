#include "shell.h"
#include "../drivers/screen.h"

void putchar_sh(struct def_shell *sh, char c) {
  putchar(sh->appointed_screen, c);
  if (c == '\n') {
    shellexec(sh);
    sh->current_index = 0;
    for (int i = 0; i < 256; i++) {
      sh->current_input[i] = 0;
    }
    shell_invite(sh);

  } else {
    sh->current_input[sh->current_index] = c;
    sh->current_index++;
  }
}

void shellexec(struct def_shell *sh) {}

void shell_invite(struct def_shell * sh){
    putchar(sh->appointed_screen, '>');
}
