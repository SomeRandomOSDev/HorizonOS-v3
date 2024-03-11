#pragma once

int putc(char c)
{
	outc(c);
	UpdateCursor();
	return c;
}
