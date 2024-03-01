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
	mov ebp, stack_top
	mov esp, stack_top

	cli

	push eax ; magic number
	push ebx ; multiboot info

	call kmain

	add esp, 8 ; clean up stack

global halt
halt:
	cli
  	hlt
	jmp $

; global LoadIDT
; extern _idtr
; ; void LoadIDT()
; LoadIDT:
;     lidt [_idtr]
;     ret

section .data
align 1
times 16384 dd 0
stack_top: