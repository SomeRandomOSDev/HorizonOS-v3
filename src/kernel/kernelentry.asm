ALIGNMENT equ 1
MEMINFO equ  (1 << 1)   
FLAGS equ (ALIGNMENT | MEMINFO)
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
dd MAGIC
dd FLAGS
dd CHECKSUM

section .text
extern kmain
global _start
_start:
bits 32
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
.loop:
  	hlt
	jmp .loop

section .data
times 16384 dd 0
stack_top:

section .rodata
global _initrd
_initrd: incbin "initrd.tar"