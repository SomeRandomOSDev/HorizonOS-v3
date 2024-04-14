#pragma once

extern uint8_t _initrd;
uint8_t* initrd_begin;
uint8_t* initrd_end;

uint8_t initrd_file_count;

struct initrd_file
{
    void* address;  // Header + 512
    uint64_t size;
    enum TAR_TypeFlags type;
};

struct initrd_file initrd[256];

void initrd_Init()
{
    initrd_begin = &_initrd;
    initrd_file_count = 0;
    uint32_t address = (uint32_t)initrd_begin;
    kmemset(&TAR_emptyHeader, 0, 512);
    while(kmemcmp(&TAR_emptyHeader, (void*)address, 512))
    {
        struct TAR_Header* file = (struct TAR_Header*)address;

        initrd[initrd_file_count].address = ((void*)address) + 512;
        initrd[initrd_file_count].size = TAR_OctalStringToInt(file->size);
        initrd[initrd_file_count].type = file->typeflag;

        address += 512 + 512 * kceil(initrd[initrd_file_count].size / 512.f);
        initrd_file_count++;
    }
    initrd_end = (void*)address;
}

void initrd_ListFiles()
{
    for(uint8_t i = 0; i < initrd_file_count; i++)
    {
        struct initrd_file file = initrd[i];
        struct TAR_Header* header = (struct TAR_Header*)(file.address - 512);
        kprintf("%s %s %uB\n", header->filename, TAR_GetTypeFlagString(header), file.size);
    }
}

struct initrd_file inird_GetFile(char* filename)
{
    for(uint8_t i = 0; i < initrd_file_count; i++)
    {
        struct initrd_file file = initrd[i];
        struct TAR_Header* header = (struct TAR_Header*)(file.address - 512);
        if(!kstrcmp(filename, header->filename))
            return file;
    }

    struct initrd_file file;
    file.address = NULL;
    file.size = 0;

    return file;
}