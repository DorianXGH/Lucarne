# $(outpath)/$@ = target file
# $< = first dependency
# $^ = all dependencies

utilpath = i386elfgcc/bin
gccargs = i386-elf-gcc -ffreestanding
obj = $(wildcard *.o)
outpath = output

# First rule is the one executed when no parameters are fed to the Makefile
all: runiso

.PHONY: fonts_directory clean

os.iso: kernel.elf
	./makeiso.sh

# Notice how dependencies are built as needed
kernel.bin: kernel_entry.o kernel.o interrupts.o screen.o memmap.o page_allocator.o shell.o keyboard.o timer.o port.o isr.o idt.o util.o pdt.o pt.o enable_paging.o gdt.o loadgdt.o fonts/font_desc.o fonts/font_basic.o
	$(utilpath)/i386-elf-ld -o $(outpath)/$@ -Ttext 0x1000 $(addprefix $(outpath)/,$^) --oformat binary

kernel.elf: kernel_entry.o kernel.o interrupts.o screen.o memmap.o page_allocator.o shell.o keyboard.o timer.o port.o isr.o idt.o util.o pdt.o pt.o enable_paging.o gdt.o loadgdt.o fonts/font_desc.o fonts/font_basic.o cpuid.o
	$(utilpath)/i386-elf-ld -T link.ld $(addprefix $(outpath)/,$^) -o $(outpath)/$@

kernel_entry.o: kernel/kernel-entry.asm
	nasm $< -f elf -o $(outpath)/$@

interrupts.o: kernel/interrupts.asm
	nasm $< -f elf -o $(outpath)/$@

enable_paging.o: kernel/memory/enable_paging.asm
	nasm $< -f elf -o $(outpath)/$@

loadgdt.o: kernel/memory/loadgdt.asm
	nasm $< -f elf -o $(outpath)/$@

cpuid.o: kernel/cpuid/cpuid.asm
	nasm $< -f elf -o $(outpath)/$@

screen.o: kernel/drivers/screen.c
	$(utilpath)/$(gccargs) -c $< -o $(outpath)/$@

memmap.o: kernel/memory/memory_segment.c
	$(utilpath)/$(gccargs) -c $< -o $(outpath)/$@

page_allocator.o: kernel/memory/page_allocator.c
	$(utilpath)/$(gccargs) -c $< -o $(outpath)/$@

pdt.o: kernel/memory/pdt.c
	$(utilpath)/$(gccargs) -c $< -o $(outpath)/$@

pt.o: kernel/memory/pt.c
	$(utilpath)/$(gccargs) -c $< -o $(outpath)/$@

gdt.o: kernel/memory/gdt.c
	$(utilpath)/$(gccargs) -c $< -o $(outpath)/$@

shell.o: kernel/shell/shell.c
	$(utilpath)/$(gccargs) -c $< -o $(outpath)/$@

keyboard.o: kernel/drivers/keyboard.c
	$(utilpath)/$(gccargs) -c $< -o $(outpath)/$@

timer.o: kernel/drivers/timer.c
	$(utilpath)/$(gccargs) -c $< -o $(outpath)/$@

port.o: kernel/drivers/port.c
	$(utilpath)/$(gccargs) -c $< -o $(outpath)/$@

kernel.o: kernel/kernel.c
	$(utilpath)/$(gccargs) -c $< -o $(outpath)/$@

isr.o: kernel/isr.c
	$(utilpath)/$(gccargs) -c $< -o $(outpath)/$@

idt.o: kernel/idt.c
	$(utilpath)/$(gccargs) -c $< -o $(outpath)/$@

util.o: kernel/util.c
	$(utilpath)/$(gccargs) -c $< -o $(outpath)/$@

fonts/font_desc.o: kernel/fonts/font_desc.c fonts_directory
	$(utilpath)/$(gccargs) -c $< -o $(outpath)/$@

fonts/font_basic.o: kernel/fonts/font_basic.c fonts_directory
	$(utilpath)/$(gccargs) -c $< -o $(outpath)/$@

fonts_directory: 
	mkdir -p $(outpath)/fonts

# Rule to disassemble the kernel - may be useful to debug
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $(outpath)/$@

bootsect.bin: bootsect/bootsect.asm
	nasm $< -f bin -o $(outpath)/$@

os-image.bin: bootsect.bin kernel.bin
	cat $^ > $(outpath)/$@

run: os-image.bin
	qemu-system-x86_64 -monitor stdio -d cpu_reset -fda $(outpath)/$<

test: os-image.bin
	bochs

runiso: os.iso
	qemu-system-x86_64 -enable-kvm -cpu host -monitor stdio -d cpu_reset -cdrom $(outpath)/$<


runisobochs: os.iso
	bochs -f bochsrciso.txt

clean:
	rm -rf $(outpath)

$(info $(shell mkdir -p $(outpath)))
