global load_pdt
global enable_paging

load_pdt: ; puts the PDT pointer in cr3 which stores the PDT location
    push ebp
    mov ebp, esp
    mov eax, [esp+8]
    mov cr3, eax
    mov esp, ebp
    pop ebp
    ret

enable_paging: ; enable paging on the CPU, after this, each adress will be interpreted by the pagination system 
    push ebp
    mov ebp, esp
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    mov esp, ebp
    pop ebp
    ret
