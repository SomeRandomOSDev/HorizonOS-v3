; void _putc(char c);
global _putc
_putc:
    push ebp
    mov ebp, esp

    mov eax, 0      ; putc
    mov ebx, [ebp + 8]
    int 0x80        ; syscall

    mov esp, ebp
    pop ebp
    ret