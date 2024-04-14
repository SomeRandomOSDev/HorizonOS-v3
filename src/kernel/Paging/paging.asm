bits 32
section .text

extern page_directory
; void Paging_LoadPageDirectory();
global Paging_LoadPageDirectory
Paging_LoadPageDirectory:
    push ebp
    mov ebp, esp

    mov eax, page_directory
    mov cr3, eax

    mov esp, ebp
    pop ebp
    ret

; void Paging_Enable();
global Paging_Enable
Paging_Enable:
    mov eax, cr0
    or eax, dword (1 << 31)   ; Paging Enable bit
    mov cr0, eax

    ret
