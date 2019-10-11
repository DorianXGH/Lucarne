global load_gdt
global reload_segs

load_gdt:
    pop eax
    lgdt [eax]
    ret

reload_segs:
    pop bx
    pop ax
    push bx
    jmp 0x8:reload
reload:
    pop bx
    mov ds, bx
    mov ss, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    ret
