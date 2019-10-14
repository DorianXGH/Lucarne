global load_gdt
global reload_segs
extern dt

load_gdt:
    lgdt [dt]
    ;jmp $
    jmp 0x08:reload
    ret

reload_segs:
    pop bx
    pop ax
    push bx
    jmp 0x8:reload
reload:
    mov ebx, 0x10
    mov ds, ebx
    mov ss, ebx
    mov es, ebx
    mov fs, ebx
    mov gs, ebx
    ret
