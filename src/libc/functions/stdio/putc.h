#pragma once

void putc(char c)
{
	outc(c);
	UpdateCursor();
}
