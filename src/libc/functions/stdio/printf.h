#pragma once

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