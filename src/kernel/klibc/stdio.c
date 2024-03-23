#pragma once

// void ShowCursor(uint8_t scanlineStart, uint8_t scanlineEnd)
// {
// 	outb(0x3d4, 0x0a);
// 	outb(0x3d5, (inb(0x3d5) & 0xc0) | scanlineStart);
 
// 	outb(0x3d4, 0x0b);
// 	outb(0x3d5, (inb(0x3d5) & 0xe0) | scanlineEnd);
// }

// void HideCursor()
// {
// 	outb(0x3d4, 0x0a);
// 	outb(0x3d5, 0x20);
// }

// void ResetCursor()
// {
// 	ShowCursor(14, 15);
// }

// void SetCursorPos(uint16_t pos)
// {
// 	outb(0x3d4, 0x0f);
// 	outb(0x3d5, (pos & 0xff));
// 	outb(0x3d4, 0x0e);
// 	outb(0x3d5, ((pos >> 8) & 0xff));
// }

// void UpdateCursor()
// {
// 	// textCursor %= 80 * 25;
// 	SetCursorPos(textCursor);
// }

// void ClearScreen(char c)
// {
// 	for(uint16_t i = 0; i < 80 * 25; i++)
// 	{
// 		VRAM_buffer[i]._char = c;
// 		VRAM_buffer[i].color = textColor;

// 		VRAM[i] = VRAM_buffer[i];
// 	}

// 	// memcpy((void*)VRAM, (void*)VRAM_buffer, 80 * 25 * 2);

// 	// textCursor = 0;
// 	// UpdateCursor();
// }

// void outc(char c)
// {
// 	switch(c)
// 	{
// 	case '\n':
// 		textCursor += 80;

// 	case '\r':
// 		textCursor /= 80;
// 		textCursor *= 80;

// 		break;

// 	case '\b':
// 		textCursor--;
// 		outc(' ');
// 		textCursor--;

// 		break;

// 	case '\t':
// 	{
// 		// for(uint8_t i = 0; i < TAB_LENGTH; i++)
// 		uint8_t firstTabX = (textCursor % 80) / TAB_LENGTH;
// 		while(firstTabX == (textCursor % 80) / TAB_LENGTH)
// 			outc(' ');

// 		break;
// 	}

// 	default:
// 		// VRAM_buffer[textCursor]._char = c;
// 		// VRAM_buffer[textCursor].color = textColor;

// 		// VRAM[textCursor] = VRAM_buffer[textCursor];

// 		VRAM[textCursor]._char = c;
// 		VRAM[textCursor].color = textColor;

// 		textCursor++;
// 	}

// 	// while((textCursor / 80) >= 25)	// Last line
// 	// {
// 	// 	for(uint16_t i = 0; i < 80 * 24; i++)
// 	// 		VRAM_buffer[i] = VRAM_buffer[i + 80];
// 	// 	for(uint8_t i = 0; i < 80; i++)
// 	// 	{
// 	// 		VRAM_buffer[i + 24 * 80]._char = ' ';
// 	// 		VRAM_buffer[i + 24 * 80].color = FG_WHITE | BG_BLACK;
// 	// 	}
// 	// 	for(uint16_t i = 0; i < 80 * 25; i++)
// 	// 		VRAM[i] = VRAM_buffer[i];
// 	// 	textCursor -= 80;
// 	// }
// }

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

void printd(int32_t val)
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

void printu(uint32_t val)
{
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

void printx(uint32_t val)
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

void printX(uint32_t val)
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
				printd(*(int32_t*)arg);

				break;

			case 'u':
				printu(*(uint32_t*)arg);

				break;

			case 'x':
				printx(*(uint32_t*)arg);

				break;

			case 'X':
				printX(*(uint32_t*)arg);

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

char* gets(char* str)
{
	uint16_t cursor_start_pos = textCursor;
    uint8_t size = 0;
    while(true)
    {
        if(kb_text_key_down)
        {
            uint16_t key = PS2_KB_GetTextKey();
			if(key == '\n')
				break;
            if(!(key == '\b' && cursor_start_pos == textCursor))
            {
                if(key != '\b' && key != '\n' && key != KB_DELETE)
                {
                    str[size] = key;
                    size++;
                    putc(key);
                }
                else if(key == '\b')
                {
                    size--;
                    putc('\b');
                }
            }
        }
    }

    str[size] = '\0';

    putc('\n');

	while(PS2_KB_GetKeyState('\n'));

    return str;
}