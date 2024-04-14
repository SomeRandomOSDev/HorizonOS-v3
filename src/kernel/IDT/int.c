#pragma once

void kernelPanic(uint8_t intNb, uint8_t errorCode)
{
    // DisablePaging();
    DisableInterrupts();
    textColor = BG_BLUE;
    ClearScreen(' ');
    textCursor = 4 + 2 * 80;
    UpdateCursor();
    HideCursor();
    textColor = (FG_LIGHTRED | BG_BLUE);
    kputs("Kernel panic\n\n\t");
    textColor = (FG_WHITE | BG_BLUE);
    kprintf("Exception number: %u\n\n\t", intNb);
    kprintf("Error:       %s\n\t", errorString[intNb]);
    kprintf("Error code:  0x%x\n\n\t", errorCode);

    // kprintf("cr0:         0x%x\n\t", GetCR0());
    // kprintf("cr2:         0x%x\n\t", GetCR2());
    // kprintf("cr3:         0x%x\n\n\t", GetCR3());

    // kprintf("eip:         0x%x\n\t", currTask->registers.eip);
    // kprintf("cs:          0x%x\n\t", currTask->registers.cs);
    // kprintf("ds:          0x%x\n\t", currTask->registers.ds);
    // kprintf("ss:          0x%x\n\n\t", currTask->registers.ss);

    // kprintf("task esp:    0x%x\n\t", currTask->registers.useresp);

    // kprintf("esp:         0x%x\n\t", currTask->registers.esp);
    // kprintf("ebp:         0x%x\n\t", currTask->registers.ebp);
    // kprintf("stack size:  %i bytes\n\t", currTask->registers.ebp - currTask->registers.esp);
    halt();
}

void InterruptHandler(struct IntParams params)
{
    if(params.interruptNumber < 32)            // ISR
    {
        kernelPanic(params.interruptNumber, params.errorCode);
        return;
    }
    else if(params.interruptNumber < 32 + 16)  // IRQ
    {
        uint8_t irqNumber = params.interruptNumber - 32;

        if(irqNumber == 7 && !(PIC_GetISR() >> 7))
            return;
        if(irqNumber == 15 && !(PIC_GetISR() >> 15))
        {
            outb(PIC1_CMD, PIC_EOI);
	        io_wait();
            return;
        }

        switch (irqNumber)
        {
        case 0:
            HandleIRQ0();
            break;

        case 1:
            HandleIRQ1();
            break;

        default:
            break;
        }

        PIC_SendEOI(irqNumber);

        return;
    }
    else if(params.interruptNumber == 0x80)    // syscall
    {
        switch(params.eax)
        {
        case 0:
            kputc((char)params.ebx);
            break;
        }
    }
}