rm iso/boot/kernel.elf
cp kernel.elf iso/boot/
genisoimage -R                              \
            -b boot/grub/grub               \
            -no-emul-boot                   \
            -boot-load-size 4               \
            -A os                           \
            -input-charset utf8             \
            -quiet                          \
            -boot-info-table                \
            -o os.iso                       \
            iso
