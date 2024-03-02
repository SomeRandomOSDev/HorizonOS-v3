#pragma once

char* errorString[32] = 
{
    "DIVISION_ERROR",
    "DEBUG",
    "NON-MASKABLE_INTERRUPT",
    "BREAKPOINT",
    "OVERFLOW",
    "BOUND_RANGE_EXCEEDED",
    "INVALID_OPCODE",
    "DEVICE_NOT_AVAILABLE",
    "DOUBLE_FAULT",
    "COPROCESSOR_SEGMENT_OVERRUN",
    "INVALID_TSS",
    "SEGMENT_NOT_PRESENT",
    "STACK_SEGMENT_FAULT",
    "GENERAL_PROTECTION_FAULT",
    "PAGE_FAULT",
    "",
    "X87_FLOATING_POINT_EXCEPTION",
    "ALIGNMENT_CHECK",
    "MACHINE_CHECK",
    "SIMD_FLOATING_POINT_EXCEPTION",
    "VIRTUALIZATION_EXCEPTION",
    "CONTROL_PROTECTION_EXCEPTION",
    "",
    "",
    "",
    "",
    "",
    "",
    "HYPERVISOR_INJECTION_EXCEPTION",
    "VMM_COMMUNICATION_EXCEPTION",
    "SECURITY_EXCEPTION",
    ""
};

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
    puts("Kernel panic\n\n\t");
    textColor = (FG_WHITE | BG_BLUE);
    printf("Exception number: %u\n\n\t", intNb);
    printf("Error:       %s\n\t", errorString[intNb]);
    printf("Error code:  0x%x\n\n\t", errorCode);

    // printf("cr0:         0x%x\n\t", GetCR0());
    // printf("cr2:         0x%x\n\t", GetCR2());
    // printf("cr3:         0x%x\n\n\t", GetCR3());

    // printf("eip:         0x%x\n\t", currTask->registers.eip);
    // printf("cs:          0x%x\n\t", currTask->registers.cs);
    // printf("ds:          0x%x\n\t", currTask->registers.ds);
    // printf("ss:          0x%x\n\n\t", currTask->registers.ss);

    // printf("task esp:    0x%x\n\t", currTask->registers.useresp);

    // printf("esp:         0x%x\n\t", currTask->registers.esp);
    // printf("ebp:         0x%x\n\t", currTask->registers.ebp);
    // printf("stack size:  %i bytes\n\t", currTask->registers.ebp - currTask->registers.esp);
    halt();
}

void InterruptHandler(uint8_t interruptNumber, uint8_t errorCode)
{
    if(interruptNumber < 32)            // ISR
    {
        kernelPanic(interruptNumber, errorCode);
        return;
    }
    else if(interruptNumber < 32 + 16)  // IRQ
    {
        uint8_t irqNumber = interruptNumber - 32;

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
}