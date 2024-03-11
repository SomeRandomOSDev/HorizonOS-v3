#ifndef _STDIO_H
#define _STDIO_H 1

typedef struct
{
  // char path[256];
} FILE;

#define EOF	      (-1)

extern void outc(char c);
extern int putc(char c);
extern int puts(char* str);
extern int printf(char* fmt, ...);

#endif