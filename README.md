# HorizonOS-v3
 A (very) simple x86 hobby operating system written in C and ASM (Intel Syntax)

## Installation
To build "horizonos.iso"
```sh
make all
```
 
## Features
- ✅ Implement basic text output
    - ✅ putc
    - ✅ puts
    - ✅ printf
- ✅ Create a basic memory manager
    - ✅ malloc
    - ✅ free
- ✅ Add a GDT
- ✅ Add an IDT
- ✅ Add the 32 exceptions in the IDT
- ✅ Handle IRQs
    - ✅ Handle PIT's channel 0
    - ✅ Handle PS/2 keyboard
    - ⬜ Handle PS/2 mouse
    - ✅ Handle spurious IRQs
- ✅ Add PCI bus scanning
- ⬜ Add paging
- ⬜ Add user mode
- ⬜ Create a C library
- ⬜ Add PRNGs
    - ⬜ LCGs
    - ⬜ Mersene Twister
- ⬜ Implement a basic ATA driver
- ⬜ Implement the FAT file system
- ⬜ Add a USB driver
