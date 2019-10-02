make_memmap:
    pusha
    mov di, 0x0
    mov ebx, 0x0 ; first desc
    push es
    mov ax, MEMMAP_SEG
    mov es, ax ; descriptor loc
make_memmap_next:
    mov eax, 0xE820 ; get desc
    mov ecx, 24 ; len of the struture
    mov edx, 534D4150h ; 'SMAP'
    int 0x15
    jc make_memmap_ret
    cmp ebx, 0
    je make_memmap_ret
    add di, 24
    jmp make_memmap_next

make_memmap_ret:
    pop es
    popa
    ret
