ENTRY(_start)
/* STARTUP("bin/kernelentry.o") */

INPUT
(
	"bin/kernelentry.o"
 	"bin/kmain.o"
	"bin/gdt.o"
)
 
SECTIONS
{
	. = 0x100000;
	_kernelStart = .;
 
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}
 
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)

		_kernelEnd = .;
	}
 
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}