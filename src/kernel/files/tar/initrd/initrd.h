#pragma once

extern uint8_t _initrd;
uint8_t* initrd_begin;
uint8_t* initrd_end;

uint8_t initrd_file_count;

struct initrd_file
{
    void* address;
    uint64_t size;
};

void initrd_Init()
{
    initrd_begin = &_initrd;
    // initrd_end = initrd_begin;
    initrd_file_count = 0;
    uint32_t address = (uint32_t)initrd_begin;
    memset(&TAR_emptyHeader, 0, 512);
    while(memcmp(&TAR_emptyHeader, (void*)address, 512))
    // while(!memcmp(((struct TAR_Header*)address)->USTAR, "ustar", 5))
    {
        struct TAR_Header* file = (struct TAR_Header*)address;
        address += 512 + 512 * ceil(TAR_OctalStringToInt(file->size) / 512.f);
        initrd_file_count++;
    }
}

void inird_GetFile(struct initrd_file* file_info)
{
}