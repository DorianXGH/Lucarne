[extern cpuid_get_features]

cpuid_get_features: 
    push ebp
    mov ebp, esp

    mov eax, 0
    cpuid
    mov eax, 1
    cpuid

    mov ebx, [ebx-4]
    mov [ebx], edx
    mov ebx, [ebx-8]
    mov [ebx], ecx
    
    mov esp, ebp
    pop ebp
    
    ret