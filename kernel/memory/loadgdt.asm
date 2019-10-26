global load_gdt
global reload_segs
extern dt

load_gdt: ; load the GDT
    lgdt [dt]
    jmp 0x08:reload
    ret

reload_segs: ; reload the segment segisters
    pop bx
    pop ax
    push bx
    jmp 0x8:reload
reload: ; reload the segment segisters
    mov ebx, 0x10
    mov ds, ebx
    mov ss, ebx
    mov es, ebx
    mov fs, ebx
    mov gs, ebx
    ret
