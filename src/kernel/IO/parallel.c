#pragma once

void InitParallel()
{
    LPT1 = *(uint16_t*)0x408;
    if(!LPT1)   // Default
        LPT1 = 0x378;

    LPT2 = *(uint16_t*)0x40a;
    if(!LPT2)   // Default
        LPT2 = 0x278;

    LPT3 = *(uint16_t*)0x40c;
    if(!LPT3)   // Default
        LPT3 = 0x3bc;
}

// void Parallel_SendByte(uint16_t port, uint8_t byte)
// {
//     while (inb(port + PARALLEL_STATUS_OFFSET) & PARALLEL_STATUS_BUSY)
//         sleep(10);

//     outb(port + PARALLEL_DATA_OFFSET, byte);

//     uint8_t ctrl = inb(port + PARALLEL_CONTROL_OFFSET);
//     outb(port + PARALLEL_CONTROL_OFFSET, ctrl | PARALLEL_CONTROL_STROBE);
//     sleep(10);
//     outb(port + PARALLEL_CONTROL_OFFSET, ctrl);

//     while (!(inb(port + PARALLEL_STATUS_OFFSET) & PARALLEL_STATUS_BUSY))
//         sleep(10);
// }