[extern cpuid_get_features]
[extern cpuid_enable_sse]

cpuid_get_features: 
    push ebp
    mov ebp, esp
    
    mov eax, 0
    cpuid
    mov eax, 1
    cpuid

    mov dword ebx, [ebp+8]
    mov dword [ebx], edx
    mov dword ebx, [ebp+12]
    mov dword [ebx], ecx
    
    mov esp, ebp
    pop ebp

    ret

cpuid_enable_sse:
    ;now enable SSE and the like
    mov eax, cr0
    and ax, 0xFFFB		;clear coprocessor emulation CR0.EM
    or ax, 0x2			;set coprocessor monitoring  CR0.MP
    mov cr0, eax
    mov eax, cr4
    or ax, 3 << 9		;set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
    mov cr4, eax
    ret