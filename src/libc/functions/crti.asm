section .init

global _init    ;  Call global contructors
_init:
   push ebp
   mov ebp, esp
   ; crtbegin.o's init section

section .fini

global _fini    ; Call global destructors
_fini:
   push ebp
   mov ebp, esp
   ; crtbegin.o's fini sectio