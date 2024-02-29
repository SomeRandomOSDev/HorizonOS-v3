#pragma once

void* memchr(const void* str, int c, size_t n)
{
    void* out = NULL;
    for(size_t i = 0; i < n; i++)
    {
        if(((uint8_t*)str)[i] == (uint8_t)c)
        {
            out = &((uint8_t*)str)[i];
            break;
        }
    }
    return out;
}

// int memcmp(const void* str1, const void* str2, size_t n);

void* memcpy(void* dest, const void* src, size_t n)
{
    for(size_t i = 0; i < n; i++)
            ((uint8_t*)dest)[i] = ((uint8_t*)src)[i];

    return dest;
}

// void *memmove(void *dest, const void *src, size_t n);

void* memset(void* ptr, int value, size_t count)
{
    for(size_t i = 0; i < count; i++)
        ((uint8_t*)ptr)[i] = (uint8_t)value;

    return ptr;
}

// TODO: Add more functions