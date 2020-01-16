

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

.tutor: ; int tutor(int childpid, int tutorpid) , 
; the childpid-defined process will have its parent reassigned to be the tutorpid-defined (0 means root process (NOT PARENT)) process, given the tutoring process is waiting for a process, otherwise, wait for the tutoring process
; If 0 is passed as childpid, tutorpid is ignored and it waits for a process to tutor, then returns the childpid received
    push ebp
    mov ebp, esp

    mov eax, 5
    mov dword ebx, [ebp+8]
    mov dword ecx, [ebp+12]
    int 48
    
    mov esp, ebp
    pop ebp

    ret

.kill: ; void kill(int pid) , kills pid-defined process, 0 means self
    push ebp
    mov ebp, esp

    mov eax, 6
    mov dword ebx, [ebp+8]
    int 48
    
    mov esp, ebp
    pop ebp

    ret

.allow_timeout:; void allow_timeout(int pid, int timeoutms) , set blocking syscalls timeout delay of pid-defined process, pid 0 means self, timeoutms 0 means no timeout
    push ebp
    mov ebp, esp

    mov eax, 7
    mov dword ebx, [ebp+8]
    mov dword ecx, [ebp+12]
    int 48
    
    mov esp, ebp
    pop ebp

    ret

.curse: ; void curse(int pid) , the pid-defined process gets skipped during scheduling until forgiven, 0 means self
    push ebp
    mov ebp, esp

    mov eax, 8
    mov dword ebx, [ebp+8]
    int 48
    
    mov esp, ebp
    pop ebp

    ret

.forgive: ; void forgive(int pid) , the pid-defined process gets no longer skipped during scheduling
    push ebp
    mov ebp, esp

    mov eax, 9
    mov dword ebx, [ebp+8]
    int 48
    
    mov esp, ebp
    pop ebp

    ret