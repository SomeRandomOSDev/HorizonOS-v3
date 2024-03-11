; void putc(char c);
global putc
putc:
    push ebp
    mov ebp, esp

    mov eax, 0      ; putc
    mov ebx, [ebp + 8]
    int 0x80        ; syscall

    mov esp, ebp
    pop ebp
    ret