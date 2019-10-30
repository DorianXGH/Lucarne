[extern cpuid_get_features]

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