global LoadGDT
extern gdtPtr
; void LoadGDT()
LoadGDT:
    lgdt  [gdtPtr]
    jmp 0x08:.reloadSeg
.reloadSeg:
    mov   ax, 0x10
    mov   ds, ax
    mov   es, ax
    mov   fs, ax
    mov   gs, ax
    mov   ss, ax
 
    ret