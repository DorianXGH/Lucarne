#include "isr.h"
#include "drivers/screen.h"
#include "drivers/port.h"
#include "idt.h"
#include "util.h"

isr_t interrupt_handlers[256];
extern struct def_vga_screen default_screen;
/* Can't do this with a loop because we need the address
 * of the function names */
void isr_install() {
  set_idt_gate(0, (int)isr0);
  set_idt_gate(1, (int)isr1);
  set_idt_gate(2, (int)isr2);
  set_idt_gate(3, (int)isr3);
  set_idt_gate(4, (int)isr4);
  set_idt_gate(6, (int)isr6);
  set_idt_gate(7, (int)isr7);
  set_idt_gate(8, (int)isr8);
  set_idt_gate(9, (int)isr9);
  set_idt_gate(10, (int)isr10);
  set_idt_gate(11, (int)isr11);
  set_idt_gate(12, (int)isr12);
  set_idt_gate(13, (int)isr13);
  set_idt_gate(14, (int)isr14);
  set_idt_gate(15, (int)isr15);
  set_idt_gate(16, (int)isr16);
  set_idt_gate(17, (int)isr17);
  set_idt_gate(18, (int)isr18);
  set_idt_gate(19, (int)isr19);
  set_idt_gate(20, (int)isr20);
  set_idt_gate(21, (int)isr21);
  set_idt_gate(22, (int)isr22);
  set_idt_gate(23, (int)isr23);
  set_idt_gate(24, (int)isr24);
  set_idt_gate(25, (int)isr25);
  set_idt_gate(26, (int)isr26);
  set_idt_gate(27, (int)isr27);
  set_idt_gate(28, (int)isr28);
  set_idt_gate(29, (int)isr29);
  set_idt_gate(30, (int)isr30);
  set_idt_gate(31, (int)isr31);

  // Remap the PIC
  port_byte_out(0x20, 0x11);
  port_byte_out(0xA0, 0x11);
  port_byte_out(0x21, 0x20);
  port_byte_out(0xA1, 0x28);
  port_byte_out(0x21, 0x04);
  port_byte_out(0xA1, 0x02);
  port_byte_out(0x21, 0x01);
  port_byte_out(0xA1, 0x01);
  port_byte_out(0x21, 0x0);
  port_byte_out(0xA1, 0x0);

  // Install the IRQs
  set_idt_gate(32, (int)irq0);
  set_idt_gate(33, (int)irq1);
  set_idt_gate(34, (int)irq2);
  set_idt_gate(35, (int)irq3);
  set_idt_gate(36, (int)irq4);
  set_idt_gate(37, (int)irq5);
  set_idt_gate(38, (int)irq6);
  set_idt_gate(39, (int)irq7);
  set_idt_gate(40, (int)irq8);
  set_idt_gate(41, (int)irq9);
  set_idt_gate(42, (int)irq10);
  set_idt_gate(43, (int)irq11);
  set_idt_gate(44, (int)irq12);
  set_idt_gate(45, (int)irq13);
  set_idt_gate(46, (int)irq14);
  set_idt_gate(47, (int)irq15);

  // SYSCALL
  set_idt_gate(48, (int)isr48);

  set_idt(); // Load with ASM
}

/* To print the message which defines every exception */
char * exception_messages[] = {"Division By Zero",
                              "Debug",
                              "Non Maskable Interrupt",
                              "Breakpoint",
                              "Into Detected Overflow",
                              "Out of Bounds",
                              "Invalid Opcode",
                              "No Coprocessor",

                              "Double Fault",
                              "Coprocessor Segment Overrun",
                              "Bad TSS",
                              "Segment Not Present",
                              "Stack Fault",
                              "General Protection Fault",
                              "Page Fault",
                              "Unknown Interrupt",

                              "Coprocessor Fault",
                              "Alignment Check",
                              "Machine Check",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",

                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved"};

void register_interrupt_handler(char n, isr_t handler) {
  interrupt_handlers[n] = handler;
}

void irq_handler(registers_t r) {
  /* After every interrupt we need to send an EOI to the PICs
   * or they will not send another interrupt again */
  if (r.int_no >= 40)
    port_byte_out(0xA0, 0x20); /* slave */
  port_byte_out(0x20, 0x20);   /* master */

  /* Handle the interrupt in a more modular way */
  if (interrupt_handlers[r.int_no] != 0) {
    isr_t handler = interrupt_handlers[r.int_no];
    handler(r);
  }
}

void isr_handler(registers_t r) {
  putstring(&default_screen, "received interrupt: ");
  char s[3];
  int_to_ascii(r.int_no, s);
  putstring(&default_screen, s);
  newline(&default_screen);
  putstring(&default_screen, exception_messages[r.int_no]);
  newline(&default_screen);
}
