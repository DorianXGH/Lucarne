#include "keyboard.h"
#include "port.h"
#include "../isr.h"
#include "screen.h"
#include "../util.h"
#include "../shell/shell.h"

extern struct def_vga_screen default_screen;
extern struct def_shell default_shell;

static void keyboard_callback(registers_t regs)
{
    /* The PIC leaves us the scancode in port 0x60 */
    char scancode = port_byte_in(0x60);

    process_letter(scancode);
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}

void process_letter(char scancode)
{
    switch (scancode) {
        case 0x0:
            putstring(&default_screen, "ERROR");
            break;
        case 0x1:

            break;
        case 0x2:
            putchar_sh(&default_shell, '1');
            break;
        case 0x3:
            putchar_sh(&default_shell, '2');
            break;
        case 0x4:
            putchar_sh(&default_shell, '3');
            break;
        case 0x5:
            putchar_sh(&default_shell, '4');
            break;
        case 0x6:
            putchar_sh(&default_shell, '5');
            break;
        case 0x7:
            putchar_sh(&default_shell, '6');
            break;
        case 0x8:
            putchar_sh(&default_shell, '7');
            break;
        case 0x9:
            putchar_sh(&default_shell, '8');
            break;
        case 0x0A:
            putchar_sh(&default_shell, '9');
            break;
        case 0x0B:
            putchar_sh(&default_shell, '0');
            break;
        case 0x0C:
            putchar_sh(&default_shell, '-');
            break;
        case 0x0D:
            putchar_sh(&default_shell, '+');
            break;
        case 0x0E:
            // Backspace
            break;
        case 0x0F:
            putchar_sh(&default_shell, 'Tab');
            break;
        case 0x10:
            putchar_sh(&default_shell, 'Q');
            break;
        case 0x11:
            putchar_sh(&default_shell, 'W');
            break;
        case 0x12:
            putchar_sh(&default_shell, 'E');
            break;
        case 0x13:
            putchar_sh(&default_shell, 'R');
            break;
        case 0x14:
            putchar_sh(&default_shell, 'T');
            break;
        case 0x15:
            putchar_sh(&default_shell, 'Y');
            break;
        case 0x16:
            putchar_sh(&default_shell, 'U');
            break;
        case 0x17:
            putchar_sh(&default_shell, 'I');
            break;
        case 0x18:
            putchar_sh(&default_shell, 'O');
            break;
        case 0x19:
            putchar_sh(&default_shell, 'P');
            break;
        case 0x1A:
            putchar_sh(&default_shell, '[');
            break;
        case 0x1B:
            putchar_sh(&default_shell, ']');
            break;
        case 0x1C:
            putchar_sh(&default_shell, '\n');
            break;
        case 0x1D:
            // Lctrl
            break;
        case 0x1E:
            putchar_sh(&default_shell, 'A');
            break;
        case 0x1F:
            putchar_sh(&default_shell, 'S');
            break;
        case 0x20:
            putchar_sh(&default_shell, 'D');
            break;
        case 0x21:
            putchar_sh(&default_shell, 'F');
            break;
        case 0x22:
            putchar_sh(&default_shell, 'G');
            break;
        case 0x23:
            putchar_sh(&default_shell, 'H');
            break;
        case 0x24:
            putchar_sh(&default_shell, 'J');
            break;
        case 0x25:
            putchar_sh(&default_shell, 'K');
            break;
        case 0x26:
            putchar_sh(&default_shell, 'L');
            break;
        case 0x27:
            putchar_sh(&default_shell, ';');
            break;
        case 0x28:
            putchar_sh(&default_shell, '\'');
            break;
        case 0x29:
            putchar_sh(&default_shell, '`');
            break;
        case 0x2A:
            // Lshift
            break;
        case 0x2B:
            putchar_sh(&default_shell, '\\');
            break;
        case 0x2C:
            putchar_sh(&default_shell, 'Z');
            break;
        case 0x2D:
            putchar_sh(&default_shell, 'X');
            break;
        case 0x2E:
            putchar_sh(&default_shell, 'C');
            break;
        case 0x2F:
            putchar_sh(&default_shell, 'V');
            break;
        case 0x30:
            putchar_sh(&default_shell, 'B');
            break;
        case 0x31:
            putchar_sh(&default_shell, 'N');
            break;
        case 0x32:
            putchar_sh(&default_shell, 'M');
            break;
        case 0x33:
            putchar_sh(&default_shell, ',');
            break;
        case 0x34:
            putchar_sh(&default_shell, '.');
            break;
        case 0x35:
            putchar_sh(&default_shell, '/');
            break;
        case 0x36:
            // Rshift
            break;
        case 0x37:
            // keypad
            break;
        case 0x38:
            // Lalt
            break;
        case 0x39:
            putchar_sh(&default_shell, 'Spc');
            break;
        default:

            /* 'keuyp' event corresponds to the 'keydown' + 0x80
             * it may still be a scancode we haven't implemented yet, or
             * maybe a control/escape sequence */

            /*if (scancode <= 0x7f) {
             *  putstring(&default_screen, "Unknown key down");
             * } else if (scancode <= 0x39 + 0x80) {
             *  putstring(&default_screen, "key up ");
             *  print_letter(scancode - 0x80);
             * } else putstring(&default_screen, "Unknown key up");*/
            break;
    }
} /* process_letter */
