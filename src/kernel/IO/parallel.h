#pragma once

uint16_t LPT1, LPT2, LPT3;

#define PARALLEL_DATA_OFFSET      0
#define PARALLEL_STATUS_OFFSET    1
#define PARALLEL_CONTROL_OFFSET   2

#define PARALLEL_STATUS_IRQ         (1 << 2)
#define PARALLEL_STATUS_ERROR       (1 << 3)
#define PARALLEL_STATUS_SELECT_IN   (1 << 4)
#define PARALLEL_STATUS_PAPER_OUT   (1 << 5)
#define PARALLEL_STATUS_ACK         (1 << 6)
#define PARALLEL_STATUS_BUSY        (1 << 7)

#define PARALLEL_CONTROL_STROBE     (1 << 0)
#define PARALLEL_CONTROL_AUTO_LF    (1 << 1)
#define PARALLEL_CONTROL_INITIALIZE (1 << 2)
#define PARALLEL_CONTROL_SELECT     (1 << 3)
#define PARALLEL_CONTROL_IRQ_ACK    (1 << 4)
#define PARALLEL_CONTROL_BIDI       (1 << 5)

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