

.start_proc: ; pid start_proc(char* path) , 0 means empty process, returns new process id
    push ebp
    mov ebp, esp

    mov eax, 0
    mov dword ebx, [ebp+8]
    int 48
    
    mov esp, ebp
    pop ebp

    ret

.push_context:  ; void push_context(int pid) , copies context(memory + registers) to child process
    push ebp
    mov ebp, esp

    mov eax, 1
    mov dword ebx, [ebp+8]
    int 48
    
    mov esp, ebp
    pop ebp

    ret

.replace: ; void replace(int pid, char* path) , replace pid-defined (0 means self) process context by path-provided executable
    push ebp
    mov ebp, esp

    mov eax, 2
    mov dword ebx, [ebp+8]
    mov dword ecx, [ebp+12]
    int 48
    
    mov esp, ebp
    pop ebp

    ret