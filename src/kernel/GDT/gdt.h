#pragma once

struct GDT_Descriptor
{
    uint16_t size;      // The size of the table in bytes subtracted by 1
    uint32_t address;   // The linear address of the GDT (not the physical address, paging applies).
} __attribute__((__packed__));

struct GDT_Descriptor gdtPtr;

struct GDT_Entry
{   
    uint16_t limit_lo   : 16;
    uint16_t base_lo    : 16;
    uint8_t base_mid    : 8;
    uint8_t access_byte : 8;
    uint8_t limit_hi    : 4;
    uint8_t flags       : 4;
    uint8_t base_hi     : 8;
} __attribute__((__packed__));

struct GDT_Entry GDT[3];

extern void LoadGDT();

void SetupGDTEntry(struct GDT_Entry* entry, uint32_t base, uint32_t limit, uint8_t access_byte, uint8_t flags)
{
    entry->base_lo = (base & 0xffff);
    entry->base_mid = ((base >> 16) & 0xff);
    entry->base_hi = ((base >> 24) & 0xff);
    entry->limit_lo = (limit & 0xffff);
    entry->limit_hi = ((limit >> 16) & 0xf);
    entry->access_byte = access_byte;
    entry->flags = flags;
}

void InstallGDT()
{
    gdtPtr.size = sizeof(GDT) - 1;
    gdtPtr.address = (uint32_t)&GDT;

    LoadGDT();
}