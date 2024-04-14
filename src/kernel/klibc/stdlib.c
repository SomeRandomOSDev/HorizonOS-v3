#pragma once

void kabort()
{
    kprintf("\nKernel aborted.");
    halt();
}