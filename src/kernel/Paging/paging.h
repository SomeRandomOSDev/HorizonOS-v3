#pragma once

enum Paging_Privilege
{
    Supervisor = 0,
    User = 1
};

struct Page_Directory_Entry_4KB
{
    uint32_t address_hi                     : 20;   // Bits 31-12 of address
    uint8_t available_0                     : 4;
    bool zero                               : 1;    // Page Size = 4KB
    uint8_t available_1                     : 1;
    bool accessed                           : 1;
    bool cache_disable                      : 1;
    bool write_through                      : 1;
    enum Paging_Privilege user_supervisor   : 1;
    bool read_write                         : 1;
    bool present                            : 1;
} __attribute__((packed));

struct Page_Table_Entry
{
    uint32_t address_hi                     : 20;   // Bits 31-12 of address
    uint8_t available                       : 3;
    bool global                             : 1;
    bool page_attribute_table               : 1;
    bool dirty                              : 1;
    bool accessed                           : 1;
    bool cache_disable                      : 1;
    bool write_through                      : 1;
    enum Paging_Privilege user_supervisor   : 1;
    bool read_write                         : 1;
    bool present                            : 1;
} __attribute__((packed));

struct Page_Directory_Entry_4KB     page_directory[1024]    __attribute__((aligned(4096)));

struct Page_Table_Entry             page_table_0[1024]      __attribute__((aligned(4096)));
struct Page_Table_Entry             page_table_1[1024]      __attribute__((aligned(4096)));

void Paging_Init_PageDir()
{
    struct Page_Directory_Entry_4KB empty_entry;
    *(uint32_t*)&empty_entry = 0;

    for(uint16_t i = 0; i < 1024; i++)
        page_directory[i] = empty_entry;
}

void Paging_IdentityMap_PageTable(uint32_t address, enum Paging_Privilege mode, struct Page_Table_Entry* page_table)
{
    struct Page_Table_Entry entry;
    *(uint32_t*)&entry = 0;

    entry.user_supervisor = mode;
    entry.read_write = true;
    entry.present = true;

    for(uint16_t i = 0; i < 1024; i++)
    {
        entry.address_hi = i + (address >> 12); 
        page_table[i] = entry;
    }
}

void Paging_Add_PageTable(uint16_t page, struct Page_Table_Entry* page_table)
{
    struct Page_Directory_Entry_4KB entry;
    *(uint32_t*)&entry = 0;

    entry.address_hi = ((uint32_t)page_table >> 12);  // Aligned on 4KB boundaries
    entry.read_write = true;
    entry.present = true;
    
    page_directory[page] = entry;
}

extern void Paging_LoadPageDirectory(uint32_t address);
extern void Paging_Enable();