global load_pdt
global enable_paging

load_pdt:
    push ebp
    mov ebp, esp
    mov eax, 8[esp]
    mov cr3, eax
    mov esp, ebp
    pop ebp
    ret

enable_paging:
    push ebp
    mov %esp, %ebp
    mov %cr0, %eax
    or $0x80000000, %eax
    mov cr0, eax
    mov esp, ebp
    pop ebp
    ret
