global enter_v86.asm
global interrupt_10_v86.asm
enter_v86:
   mov ebp, esp               ; save stack pointer

   push dword  [ebp+4]        ; ss
   push dword  [ebp+8]        ; esp
   pushfd                     ; eflags
   or dword [esp], (1 << 17)  ; set VM flags
   push dword [ebp+12]        ; cs
   push dword  [ebp+16]       ; eip
   iret

[bits 16]
interrupt_10_v86:
    pop ax
    pop bx
    pop cx
    pop dx
    pop di
    pop si
    int 0x10
    ret
