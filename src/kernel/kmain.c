#include "includes.h"

#include "klibc/stdio.h"
#include "klibc/string.h"
#include "klibc/stdlib.h"

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

uint64_t totalMem = 0, availableMem = 0;

void kmain(multiboot_info_t* multibootInfo, uint32_t magicNumber)
{
    ClearScreen(' ');
    ResetCursor();

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

        // uint64_t addr = (mmmt->addr_high << 8) | mmmt->addr_low;
        uint64_t len = (mmmt->len_high) | mmmt->len_low;
 
        if(mmmt->type == MULTIBOOT_MEMORY_AVAILABLE) 
        {
            printf("Block address: 0x%x | Length: %d\n", 
            // (mmmt->addr_high << 8) | mmmt->addr_low, (mmmt->len_high) | mmmt->len_low);
            mmmt->addr_low, mmmt->len_low);

            availableMem += len;
        }

        totalMem += len;
    }

    uint64_t totalMem_short = totalMem;
    uint8_t totalMem_magnitude = 0;
    uint64_t availableMem_short = availableMem;
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
    printf("Total RAM: \t %d%s (%dB)\n", (uint16_t)totalMem_short, byteMagnitude[totalMem_magnitude % 5], totalMem);
    printf("Usable: \t %d%s (%dB)\n", (uint16_t)availableMem_short, byteMagnitude[availableMem_magnitude % 5], availableMem);

    while(true);
}