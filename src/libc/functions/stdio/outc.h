#pragma once

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

	case '\b':
		textCursor--;
		outc(' ');
		textCursor--;

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
		VRAM[textCursor]._char = c;
		VRAM[textCursor].color = textColor;

		textCursor++;
	}

	while((textCursor / 80) >= 25)	// Last line
	{
		memcpy(&VRAM[0], &VRAM[80], 80 * 24 * sizeof(struct Character));
		for(uint8_t i = 0; i < 80; i++)
		{
			VRAM[24 * 80 + i]._char = ' ';
			VRAM[24 * 80 + i].color = FG_WHITE | BG_BLACK;
		}

		textCursor -= 80;
	}
}