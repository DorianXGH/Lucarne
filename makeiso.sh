outpath=output
cp -r iso $outpath/
cp $outpath/kernel.elf $outpath/iso/boot/
grub-mkrescue -o $outpath/os.iso $outpath/iso
