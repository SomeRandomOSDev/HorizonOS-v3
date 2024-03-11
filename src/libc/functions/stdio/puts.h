#pragma once

int puts(char* str)
{
	while(*str)
	{
		outc(*str);
		
		str++;
	}

	UpdateCursor();

	return (int)str;
}