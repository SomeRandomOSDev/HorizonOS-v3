#pragma once

struct TAR_Header
{
    char filename[100];
    char mode[8];
    char uid[8];
    char gid[8];
    char size[12];  // Octal string
    char mtime[12];
    char chksum[8];
    char typeflag[1];
};

uint64_t TAR_OctalStringToInt(char str[12])
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