section .text

extern _init
extern main
extern exit

global _start
_start:
    call _init  ; Call global constructors
    
    call main

    call exit