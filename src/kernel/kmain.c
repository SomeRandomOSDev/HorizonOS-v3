#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

uint32_t totalMem = 0, availableMem = 0;

#include "multiboot.h"
#include "io.h"

multiboot_info_t* multibootInfo;

#include "klibc/math.h"
#include "klibc/stdio.h"
#include "klibc/string.h"
#include "klibc/stdlib.h"

#include "GDT/gdt.h"

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

void* kernelStart = &_kernelStart;
void* kernelEnd = &_kernelEnd;

void kmain(multiboot_info_t* _multibootInfo, uint32_t magicNumber)
{
    ClearScreen(' ');
    ResetCursor();

    multibootInfo = _multibootInfo;

    if(magicNumber != MULTIBOOT_BOOTLOADER_MAGIC) 
    {
        textColor = (FG_RED | BG_BLACK);
        printf("Invalid multiboot magic number (%x).\n", magicNumber);
        abort();
    }

    if(!((multibootInfo->flags >> 6) & 1)) 
    {
        textColor = (FG_RED | BG_BLACK);
        puts("Invalid memory map.\n");
        abort();
    }

    puts("Memory map :\n");
    for(uint32_t i = 0; i < multibootInfo->mmap_length; i += sizeof(multiboot_memory_map_t)) 
    {
        multiboot_memory_map_t* mmmt = (multiboot_memory_map_t*)(multibootInfo->mmap_addr + i);

        uint32_t addr = (mmmt->addr_high << 8) | mmmt->addr_low;
        uint32_t len = (mmmt->len_high) | mmmt->len_low;
 
        if(mmmt->type == MULTIBOOT_MEMORY_AVAILABLE) 
        {
            printf("Block address: 0x%x | Length: %d\n", 
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

    putc('\n');
    printf("Total RAM: \t %d%s (%dB)\n", (uint32_t)totalMem_short, byteMagnitude[totalMem_magnitude % 5], totalMem);
    printf("Usable: \t %d%s (%dB)\n", (uint32_t)availableMem_short, byteMagnitude[availableMem_magnitude % 5], availableMem);

    putc('\n');
    printf("Initializing malloc()...\n");
    initMemAlloc(256);

    printf("Loading a GDT...\n");
    
    memset(&GDT[0], 0, sizeof(struct GDT_Entry));   // NULL Descriptor

    SetupGDTEntry(&GDT[1], 0, 0xfffff, 0x9a, 0xc);  // Kernel mode code segment
    SetupGDTEntry(&GDT[2], 0, 0xfffff, 0x92, 0xc);  // Kernel mode data segment

    InstallGDT();

    while(true);
}