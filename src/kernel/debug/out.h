#pragma once

void Debug_putc(char c)
{
    outb(0xe9, c);
}