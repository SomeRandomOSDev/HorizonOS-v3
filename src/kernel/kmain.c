#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

uint32_t totalMem = 0, availableMem = 0;

#define KB 1024
#define MB (1024 * KB)
#define GB (1024 * MB)
#define TB (1024 * GB)

char byteMagnitude[5][3] = 
{
    {"B"}, {"KB"}, {"MB"}, {"GB"}, {"TB"}
};

extern uint8_t _kernelStart;
extern uint8_t _kernelEnd;

void* kernelStart;
void* kernelEnd;

#define EnableInterrupts()  asm("sti");
#define DisableInterrupts() asm("cli");

#include "multiboot.h"
#include "IO/io.h"
#include "Debug/out.h"

multiboot_info_t* multibootInfo;

#include "klibc/math.h"
#include "klibc/stdio.h"
#include "klibc/string.h"
#include "klibc/stdlib.h"

#include "IO/textio.h"

#include "IO/parallel.h"
#include "IO/ps2kb.h"
#include "IO/ps2.h"
#include "PCI/pci.h"

#include "PIT/pit.h"
#include "GDT/gdt.h"
#include "IDT/PIC.h"
#include "IDT/int.h"
#include "IDT/idt.h"
#include "IDT/syscalls.h"

//-----------------------------------------------------------------

#include "klibc/math.c"
#include "klibc/stdio.c"
#include "klibc/string.c"
#include "klibc/stdlib.c"
#include "IO/textio.c"

#include "IO/parallel.c"
#include "IO/ps2kb.c"
#include "PCI/pci.c"

#include "PIT/pit.c"
#include "GDT/gdt.c"
#include "IDT/PIC.c"
#include "IDT/int.c"
#include "IDT/idt.c"

//-------------------------------------------------------

#include "files/tar/tar.h"
#include "files/tar/initrd/initrd.h"
#include "util/reboot.h"
#include "util/kmalloc.h"
#include "Paging/paging.h"

void kernel(multiboot_info_t* _multibootInfo, uint32_t magicNumber)
{
    textColor = FG_WHITE | BG_BLACK;
    textCursor = 0;
    _kstdin.stream = STDIN;
    _kstdout.stream = STDOUT;
    _kstderr.stream = STDERR;
    _klog.stream = LOG_STREAM;

    ClearScreen(' ');
    ResetCursor();

    kfprintf(klog, "Kernel loaded\n");

    multibootInfo = _multibootInfo;

    kernelStart = &_kernelStart;
    kernelEnd = &_kernelEnd;

    if(magicNumber != MULTIBOOT_BOOTLOADER_MAGIC) 
    {
        textColor = (FG_RED | BG_BLACK);
        kprintf("Invalid multiboot magic number (%x).\n", magicNumber);
        kabort();
    }

    if(!((multibootInfo->flags >> 6) & 1)) 
    {
        textColor = (FG_RED | BG_BLACK);
        kputs("Invalid memory map.\n");
        kabort();
    }

    kputs("Memory map :\n");
    for(uint32_t i = 0; i < multibootInfo->mmap_length; i += sizeof(multiboot_memory_map_t)) 
    {
        multiboot_memory_map_t* mmmt = (multiboot_memory_map_t*)(multibootInfo->mmap_addr + i);

        uint32_t addr = (mmmt->addr_high << 8) | mmmt->addr_low;
        uint32_t len = (mmmt->len_high) | mmmt->len_low;
 
        if(mmmt->type == MULTIBOOT_MEMORY_AVAILABLE) 
        {
            kprintf("Block address: 0x%x | Length: %d\n", 
            // (mmmt->addr_high << 8) | mmmt->addr_low, (mmmt->len_high) | mmmt->len_low);
            mmmt->addr_low, mmmt->len_low);

            if(addr == 0)
                availableMem += 0x78200;
            else
                availableMem += len;
        }

        totalMem += len;
    }

    uint32_t totalMem_short = totalMem;
    uint8_t totalMem_magnitude = 0;
    uint32_t availableMem_short = availableMem;
    uint8_t availableMem_magnitude = 0;

    while(totalMem_short >= 1024)
    {
        totalMem_short /= 1024;
        totalMem_magnitude++;
    }

    while(availableMem_short >= 1024)
    {
        availableMem_short /= 1024;
        availableMem_magnitude++;
    }

    kputc('\n');
    kprintf("Total RAM: \t %d%s (%dB)\n", (uint32_t)totalMem_short, byteMagnitude[totalMem_magnitude % 5], totalMem);
    kprintf("Usable: \t %d%s (%dB)\n", (uint32_t)availableMem_short, byteMagnitude[availableMem_magnitude % 5], availableMem);
    kprintf("Kernel start: 0x%x\n", kernelStart);
    kprintf("Kernel end:   0x%x\n", kernelEnd);
    kprintf("Kernel size:  %d\n", kernelEnd - kernelStart);

    // while(true);

    kputc('\n');

    kprintf("Loading a GDT...");
    kmemset(&GDT[0], 0, sizeof(struct GDT_Entry));   // NULL Descriptor
    SetupGDTEntry(&GDT[1], 0, 0xfffff, 0x9a, 0xc);  // Kernel mode code segment
    SetupGDTEntry(&GDT[2], 0, 0xfffff, 0x92, 0xc);  // Kernel mode data segment
    InstallGDT();
    kprintf(" | Done\n");

    kprintf("Loading an IDT...");
    InstallIDT();
    kprintf(" | Done\n");

    kprintf("Initializing the PIC...");
    PIC_Remap(32, 32 + 8);
    kprintf(" | Done\n");

    kprintf("Initializing the PIT...");
    PIT_Channel0_SetFrequency(1000);
    kprintf(" | Done\n");

    kprintf("Initializing the keyboard...");
    kb_layout = KB_AZERTY;
    PS2_KB_Init();
    PS2_KB_ResetKeyboard();
    PS2_KB_SetScancodeSet(2);
    kprintf(" | Done\n");

    kprintf("Initializing memory allocation...");
    initMemAlloc(256);
    kprintf(" | Done\n");

    kprintf("Initializing parallel ports...");
    InitParallel();
    kprintf(" | Done\n");

    kputc('\n');

    kprintf("Scanning PCI buses...\n");
    PCI_ScanBuses();
    kprintf("...Done\n");

    kputc('\n');

    kprintf("Initializing the initrd...");
    initrd_Init();
    kprintf(" | Done\n\n");

    initrd_ListFiles();

    kputc('\n');

    kprintf("Initializing paging...");

    Paging_Init_PageDir();

    Paging_IdentityMap_PageTable(0 * MB, Supervisor, &page_table_0[0]);
    Paging_Add_PageTable(0, &page_table_0[0]);

    Paging_LoadPageDirectory((uint32_t)&page_directory[0]);
    // Paging_Enable();

    kprintf(" | Done\n\n");

    EnableInterrupts();

    while(true)
    {
        kprintf("user: ~$ ");
        char buffer[80];
        kgets(&buffer[0]);
    }
}