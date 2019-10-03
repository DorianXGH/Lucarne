# $@ = target file
# $< = first dependency
# $^ = all dependencies

utilpath = /usr/local/i386elfgcc/bin
gccargs = i386-elf-gcc -ffreestanding

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Notice how dependencies are built as needed
kernel.bin: kernel_entry.o kernel.o screen.o isr.o idt.o util.o interrupts.o port.o keyboard.o timer.o shell.o memmap.o
	$(utilpath)/i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel_entry.o: kernel/kernel-entry.asm
	nasm $< -f elf -o $@

interrupts.o: kernel/interrupts.asm
	nasm $< -f elf -o $@

screen.o: kernel/drivers/screen.c
	$(utilpath)/$(gccargs) -c $< -o $@

memmap.o: kernel/memory/memory_segment.c
	$(utilpath)/$(gccargs) -c $< -o $@

shell.o: kernel/shell/shell.c
	$(utilpath)/$(gccargs) -c $< -o $@

keyboard.o: kernel/drivers/keyboard.c
	$(utilpath)/$(gccargs) -c $< -o $@

timer.o: kernel/drivers/timer.c
	$(utilpath)/$(gccargs) -c $< -o $@

port.o: kernel/drivers/port.c
	$(utilpath)/$(gccargs) -c $< -o $@

kernel.o: kernel/kernel.c
	$(utilpath)/$(gccargs) -c $< -o $@

isr.o: kernel/isr.c
	$(utilpath)/$(gccargs) -c $< -o $@

idt.o: kernel/idt.c
	$(utilpath)/$(gccargs) -c $< -o $@

util.o: kernel/util.c
	$(utilpath)/$(gccargs) -c $< -o $@

# Rule to disassemble the kernel - may be useful to debug
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

bootsect.bin: bootsect/bootsect.asm
	nasm $< -f bin -o $@

os-image.bin: bootsect.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	qemu-system-x86_64 -fda $<

clean:
	rm *.bin *.o *.dis
