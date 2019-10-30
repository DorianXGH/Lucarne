[extern cpuid_get_features]

cpuid_get_features: 
    push ebp
    mov ebp, esp
    
    mov eax, 0
    cpuid
    mov eax, 1
    cpuid

    mov ebx, [ebp+4]
    mov [ebx], edx
    mov ebx, [ebp+8]
    mov [ebx], ecx
    
    mov esp, ebp
    pop ebp
    
    ret