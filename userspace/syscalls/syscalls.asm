

.start_proc: ; int start_proc(char* path) , creates process from path-provided executable, 0 means empty process, returns new process id
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

.wait: ; int wait(int pid) , wait for pid-defined proces's signal, 0 means parent
    push ebp
    mov ebp, esp

    mov eax, 3
    mov dword ebx, [ebp+8]
    int 48
    
    mov esp, ebp
    pop ebp

    ret

.signal: ; void signal(int pid, int message) , wait for pid-defined proces's wait, then sends the message, 0 means parent
    push ebp
    mov ebp, esp

    mov eax, 4
    mov dword ebx, [ebp+8]
    mov dword ecx, [ebp+12]
    int 48
    
    mov esp, ebp
    pop ebp

    ret