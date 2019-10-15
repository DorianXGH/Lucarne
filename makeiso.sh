rm iso/boot/kernel.elf
cp kernel.elf iso/boot/
grub-mkrescue -o os.iso iso
