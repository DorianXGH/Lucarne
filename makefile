# $@ = target file
# $< = first dependency
# $^ = all dependencies

utilpath = i386elfgcc/bin
gccargs = i386-elf-gcc -ffreestanding
obj = $(wildcard *.o)

# First rule is the one executed when no parameters are fed to the Makefile
all: run

os.iso: kernel.elf
	./makeiso.sh
# Notice how dependencies are built as needed
kernel.bin: kernel_entry.o kernel.o interrupts.o screen.o memmap.o page_allocator.o shell.o keyboard.o timer.o port.o isr.o idt.o util.o pdt.o pt.o enable_paging.o gdt.o loadgdt.o fonts/font_desc.o fonts/font_basic.o
	$(utilpath)/i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: kernel_entry.o kernel.o interrupts.o screen.o memmap.o page_allocator.o shell.o keyboard.o timer.o port.o isr.o idt.o util.o pdt.o pt.o enable_paging.o gdt.o loadgdt.o fonts/font_desc.o fonts/font_basic.o
	$(utilpath)/i386-elf-ld -T link.ld $^ -o $@

kernel_entry.o: kernel/kernel-entry.asm
	nasm $< -f elf -o $@

interrupts.o: kernel/interrupts.asm
	nasm $< -f elf -o $@

enable_paging.o: kernel/memory/enable_paging.asm
	nasm $< -f elf -o $@

loadgdt.o: kernel/memory/loadgdt.asm
	nasm $< -f elf -o $@

screen.o: kernel/drivers/screen.c
	$(utilpath)/$(gccargs) -c $< -o $@

memmap.o: kernel/memory/memory_segment.c
	$(utilpath)/$(gccargs) -c $< -o $@

page_allocator.o: kernel/memory/page_allocator.c
	$(utilpath)/$(gccargs) -c $< -o $@

pdt.o: kernel/memory/pdt.c
	$(utilpath)/$(gccargs) -c $< -o $@

pt.o: kernel/memory/pt.c
	$(utilpath)/$(gccargs) -c $< -o $@

gdt.o: kernel/memory/gdt.c
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

fonts/font_desc.o: kernel/fonts/font_desc.c
	$(utilpath)/$(gccargs) -c $< -o $@

fonts/font_basic.o: kernel/fonts/font_basic.c
	$(utilpath)/$(gccargs) -c $< -o $@




# Rule to disassemble the kernel - may be useful to debug
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

bootsect.bin: bootsect/bootsect.asm
	nasm $< -f bin -o $@

os-image.bin: bootsect.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	qemu-system-x86_64 -monitor stdio -d cpu_reset -fda $<

test: os-image.bin
	bochs

runiso: os.iso
	qemu-system-x86_64 -monitor stdio -d cpu_reset -cdrom $<

runisobochs: os.iso
	bochs -f bochsrciso.txt

clean:
	rm *.bin *.o *.dis
