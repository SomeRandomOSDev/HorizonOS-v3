#pragma once

void puts(char* str)
{
	while(*str)
	{
		outc(*str);
		
		str++;
	}

	UpdateCursor();
}