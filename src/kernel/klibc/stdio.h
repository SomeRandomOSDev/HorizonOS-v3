#pragma once

#define FG_BLACK         0x00
#define FG_BLUE          0x01
#define FG_GREEN         0x02
#define FG_CYAN          0x03
#define FG_RED           0x04
#define FG_MAGENTA       0x05
#define FG_BROWN         0x06
#define FG_LIGHTGRAY     0x07
#define FG_DARKGRAY      0x08
#define FG_LIGHTBLUE     0x09
#define FG_LIGHTGREEN    0x0a
#define FG_LIGHTCYAN     0x0b
#define FG_LIGHTRED      0x0c
#define FG_LIGHTMAGENTA  0x0d
#define FG_YELLOW        0x0e
#define FG_WHITE         0x0f
 
#define BG_BLACK         0x00
#define BG_BLUE          0x10
#define BG_GREEN         0x20
#define BG_CYAN          0x30
#define BG_RED           0x40
#define BG_MAGENTA       0x50
#define BG_BROWN         0x60
#define BG_LIGHTGRAY     0x70
#define BG_DARKGRAY      0x80
#define BG_LIGHTBLUE     0x90
#define BG_LIGHTGREEN    0xa0
#define BG_LIGHTCYAN     0xb0
#define BG_LIGHTRED      0xc0
#define BG_LIGHTMAGENTA  0xd0
#define BG_YELLOW        0xe0
#define BG_WHITE         0xf0

#define TAB_LENGTH       4

uint16_t textCursor = 0;
uint8_t textColor = (FG_WHITE | BG_BLACK);

void ShowCursor(uint8_t scanlineStart, uint8_t scanlineEnd)
{
	outb(0x3d4, 0x0a);
	outb(0x3d5, (inb(0x3d5) & 0xc0) | scanlineStart);
 
	outb(0x3d4, 0x0b);
	outb(0x3d5, (inb(0x3d5) & 0xe0) | scanlineEnd);
}

void HideCursor()
{
	outb(0x3d4, 0x0a);
	outb(0x3d5, 0x20);
}

void ResetCursor()
{
	ShowCursor(14, 15);
}

void SetCursorPos(uint16_t pos)
{
	outb(0x3d4, 0x0f);
	outb(0x3d5, (pos & 0xff));
	outb(0x3d4, 0x0e);
	outb(0x3d5, ((pos >> 8) & 0xff));
}

void UpdateCursor()
{
	textCursor %= 80 * 25;
	SetCursorPos(textCursor);
}

void ClearScreen(char c)
{
	for(uint16_t i = 0; i < 80 * 25; i++)
	{
		*((uint8_t*)0xb8000 + i * 2) = c;
		*((uint8_t*)0xb8001 + i * 2) = textColor;
	}

	textCursor = 0;
	UpdateCursor();
}

void outc(char c)
{
	switch(c)
	{
	case '\n':
		textCursor += 80;

	case '\r':
		textCursor /= 80;
		textCursor *= 80;

		break;

	case '\t':
	{
		// for(uint8_t i = 0; i < TAB_LENGTH; i++)
		uint8_t firstTabX = (textCursor % 80) / TAB_LENGTH;
		while(firstTabX == (textCursor % 80) / TAB_LENGTH)
			outc(' ');

		break;
	}

	default:
		*((uint8_t*)0xb8000 + 2 * textCursor) = c;
		*((uint8_t*)0xb8001 + 2 * textCursor) = textColor;

		textCursor++;
	}
}

void putc(char c)
{
	outc(c);
	UpdateCursor();
}

void puts(char* str)
{
	while(*str)
	{
		outc(*str);
		
		str++;
	}

	UpdateCursor();
}

void printd(int val)
{
	if(val < 0)
	{
		val *= -1;
		outc('-');
	}
	if(val < 10)
	{
		outc(val + '0');
	}
	else
	{
		bool first0 = true;
		uint32_t div = 1000000000;
		for(uint8_t i = 0; i < 10; i++)
		{
			uint8_t digit = (val / div) % 10;
			if(digit)
				first0 = false;
			if(!first0)
				outc(digit + '0');
			div /= 10;
		}
	}
}

char hex[16] = "0123456789abcdef";
char HEX[16] = "0123456789ABCDEF";

void printx(unsigned int val)
{
	if(val < 16)
	{
		outc(hex[val]);
	}
	else
	{
		bool first0 = true;
		uint32_t div = (1 << 28);
		for(uint8_t i = 0; i < 8; i++)
		{
			uint8_t digit = (val / div) & 0x0f;
			if(digit)
				first0 = false;
			if(!first0)
				outc(hex[digit]);
			div >>= 4;
		}
	}
}

void printX(unsigned int val)
{
	if(val < 16)
	{
		outc(HEX[val]);
	}
	else
	{
		bool first0 = true;
		uint32_t div = (1 << 28);
		for(uint8_t i = 0; i < 8; i++)
		{
			uint8_t digit = (val / div) & 0x0f;
			if(digit)
				first0 = false;
			if(!first0)
				outc(HEX[digit]);
			div >>= 4;
		}
	}
}

void printf(char* fmt, ...)
{
	uint32_t* arg = (uint32_t*)&fmt;
	arg++;

	while(*fmt)
	{
		switch(*fmt)
		{
		case '%':
			fmt++;

			switch(*fmt) // TODO: Add %f
			{
			case '%':
				outc('%');
				arg--;

				break;

			case 's':
				puts((char*)(*(uint32_t*)arg));

				break;

			case 'c':
				outc(*(char*)arg);

				break;

			case 'd':
				printd(*(int*)arg);

				break;

			case 'x':
				printx(*(int*)arg);

				break;

			case 'X':
				printX(*(int*)arg);

				break;

			default:
				outc('%');
				outc(*fmt);
				arg--;
			}

			arg++;

			break;

		default:
			outc(*fmt);
		}
		
		fmt++;
	}

	UpdateCursor();
}