#pragma once

struct TAR_Header
{
    uint8_t filename[100];
    uint8_t mode[8];
    uint8_t oid[8];     // Owner user ID
    uint8_t gid[8];     // Group user ID
    uint8_t size[12];   // Octal string
    uint8_t time[12];   // Unix format
    uint8_t checksum[8];
    uint8_t typeflag;
    uint8_t linked_filename[100];
    uint8_t USTAR[6];   // "ustar"
    uint8_t version[2];
    uint8_t owner_username[32];
    uint8_t owner_groupname[32];
    uint8_t device_major[8];
    uint8_t device_minor[8];
    uint8_t filename_prefix[155];
    // uint8_t padding[12];
};

uint8_t TAR_emptyHeader[512];

uint64_t TAR_OctalStringToInt(uint8_t str[12])
{
    uint64_t val = 0;
    uint64_t multiplier = 8589934592; // 8^11

    for(uint8_t i = 0; str[i]; i++)
    {
        val += multiplier * (str[i] - '0');
        multiplier >>= 3;   // /= 8
    }
 
    return val;
}