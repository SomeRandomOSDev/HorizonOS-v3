int printf(char* fmt, ...)
{
	uint32_t* arg = (uint32_t*)&fmt;
	arg++;

    uint16_t totalBytes = 0;

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
                totalBytes++;
				arg--;

				break;

			case 's':
				puts((char*)(*(uint32_t*)arg));
                totalBytes += strlen((char*)(*(uint32_t*)arg));

				break;

			case 'c':
				outc(*(char*)arg);
                totalBytes++;

				break;

			case 'd':
				totalBytes += printd(*(int32_t*)arg);

				break;

			case 'u':
				totalBytes += printu(*(uint32_t*)arg);

				break;

			case 'x':
				totalBytes += printx(*(uint32_t*)arg);

				break;

			case 'X':
				totalBytes += printX(*(uint32_t*)arg);

				break;

			default:
				outc('%');
				outc(*fmt);
                totalBytes += 2;
				arg--;
			}

			arg++;

			break;

		default:
			outc(*fmt);
            totalBytes++;
		}
		
		fmt++;
	}

	UpdateCursor();

    return totalBytes;
}