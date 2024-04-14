bits 32
section .text

_eip: dd 0 

extern kstdout
extern kfprintf

global kprintf
kprintf:
    mov eax, [esp]
    mov [_eip], eax ;  Save eip
    add esp, 4 ; Delete eip

    push dword [kstdout]
    call kfprintf

    jmp [_eip]