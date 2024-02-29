ALIGNMENT equ 1
MEMINFO equ  (1 << 1)   
FLAGS equ (ALIGNMENT | MEMINFO)
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM

section .text

[extern kmain]
global _start
_start:
[bits 32]
	push eax ; magic number
	push ebx ; multiboot info

	call kmain

	add esp, 8 ; clean up stack

global halt
halt:
	cli
  	hlt
	jmp $

; global LoadGDT
; extern gdtPtr
; ; void LoadGDT()
; LoadGDT:
;     lgdt  [gdtPtr]
;     jmp 0x08:.reloadCS
; .reloadCS:
; 	  mov   ax, 0x10
;     mov   ds, ax
;     mov   es, ax
;     mov   fs, ax
;     mov   gs, ax
;     mov   ss, ax
; 
;     ret

; global LoadIDT
; extern _idtr
; ; void LoadIDT()
; LoadIDT:
;     lidt [_idtr]
;     ret

section .data
align 16
times 16384 db 0
stack_top: