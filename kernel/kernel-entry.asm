[bits 32]
[extern _start] ; Define calling point. Must have same name as kernel.c 'main' function
entry:
    mov esp, 0x00300000
    mov ebp, esp
    push ebx
    call _start ; Calls the C function. The linker will know where it is placed in memory
    jmp $
align 4
multiboot_header:
%define MAGIC 0x1BADB002
%define MFLAGS  000000110b
%define CHECK  (-MAGIC-MFLAGS)
%define HEADADDR  0
%define LOADADDR  0
%define LOADENDADDR  0
%define BSSENDADDR  0
%define ENTADDR  0
%define GMODETYPE  0
%define GWIDTH  1280
%define GHEIGHT  720
%define GDEPTH  24
dd MAGIC
dd MFLAGS
dd CHECK
dd HEADADDR
dd LOADADDR
dd LOADENDADDR
dd BSSENDADDR
dd ENTADDR
dd GMODETYPE
dd GWIDTH
dd GHEIGHT
dd GDEPTH
