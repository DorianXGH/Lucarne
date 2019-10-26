[bits 32]
[extern _start] ; Define calling point.
entry:
    mov esp, 0x00300000 ; put the stack at a defined location
    mov ebp, esp ; make it a new callframe
    push ebx ; pass Multiboot info block pointer as argument
    call _start ; Calls the C function.
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
%define GWIDTH  1024
%define GHEIGHT  768
%define GDEPTH  32
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
