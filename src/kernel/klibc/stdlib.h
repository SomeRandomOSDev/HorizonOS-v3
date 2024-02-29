#pragma once

extern void halt();

void abort()
{
    textColor = FG_LIGHTRED | BG_BLACK;
    puts("Kernel aborted");
    halt();
}