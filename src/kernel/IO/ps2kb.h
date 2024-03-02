#pragma once

#include "ps2.h"

#define KB_ESCAPE      27
#define KB_BACKSPACE   '\b'
#define KB_RETURN      '\n'
#define KB_LCTRL       (0x0100 + 0)
#define KB_LSHIFT      (0x0100 + 1)
#define KB_RSHIFT      (0x0100 + 2)
#define KB_ALT         (0x0100 + 3)
#define KB_CAPS_LOCK   (0x0100 + 4)
#define KB_F1          (0x0100 + 5)
#define KB_F2          (0x0100 + 6)
#define KB_F3          (0x0100 + 7)
#define KB_F4          (0x0100 + 8)
#define KB_F5          (0x0100 + 9)
#define KB_F6          (0x0100 + 10)
#define KB_F7          (0x0100 + 11)
#define KB_F8          (0x0100 + 12)
#define KB_F9          (0x0100 + 13)
#define KB_F10         (0x0100 + 14)
#define KB_F11         (0x0100 + 15)
#define KB_F12         (0x0100 + 16)
#define KB_NUMLOCK     (0x0100 + 17)
#define KB_SCROLLLOCK  (0x0100 + 18)
#define KB_INSERT      (0x0100 + 27)
#define KB_DELETE      127
#define KB_RCTRL       (0x0100 + 29)
#define KB_é           ((uint8_t)130)
#define KB_è           ((uint8_t)138)
#define KB_ç           ((uint8_t)135)
#define KB_à           ((uint8_t)133)
#define KB_ù           ((uint8_t)151)
#define KB_DEGREE           ((uint8_t)248)
#define KB_POUND           ((uint8_t)156)
#define KB_SECTION           ((uint8_t)21)
#define KB_µ                 ((uint8_t)230)
// #define KB_É           ((uint8_t)130)
// #define KB_È           ((uint8_t)138)
// #define KB_Ç           ((uint8_t)135)
// #define KB_À           ((uint8_t)133)
// #define KB_Ù           ((uint8_t)151)
#define KB_²            ((uint8_t)253)

// Extended keys
#define KB_HOME        (0x0100 + 30)
#define KB_UP          (0x0100 + 31)
#define KB_LEFT        (0x0100 + 32)
#define KB_RIGHT       (0x0100 + 33)
#define KB_DOWN        (0x0100 + 34)
#define KB_PAGEUP      (0x0100 + 35)
#define KB_PAGEDOWN    (0x0100 + 36)
#define KB_END         (0x0100 + 37)

#define KB_ALT_GR      (0x0100 + 39)

#define KB_NUMPAD_0    (0x0100 + '0') // 48
#define KB_NUMPAD_1    (0x0100 + '1')
#define KB_NUMPAD_2    (0x0100 + '2')
#define KB_NUMPAD_3    (0x0100 + '3')
#define KB_NUMPAD_4    (0x0100 + '4')
#define KB_NUMPAD_5    (0x0100 + '5')
#define KB_NUMPAD_6    (0x0100 + '6')
#define KB_NUMPAD_7    (0x0100 + '7')
#define KB_NUMPAD_8    (0x0100 + '8')
#define KB_NUMPAD_9    (0x0100 + '9') // 57

#define KB_LED_SCROLL_LOCK (1 << 0)
#define KB_LED_NUM_LOCK    (1 << 1)
#define KB_LED_CAPS_LOCK   (1 << 2)

#define KB_ACK      0xfa
#define KB_RESEND   0xfe

#define KB_SCANCODE_SET_1   1
#define KB_SCANCODE_SET_2   2
#define KB_SCANCODE_SET_3   3

uint16_t kb_azerty_set2[128] =
{
    0,  KB_ESCAPE, '&', KB_é, '\"', '\'', '(', '-', KB_è, '_', KB_ç, KB_à, ')', '=', '\b', '\t', 
    'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$', '\n', KB_LCTRL, 'q', 's', 
    'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', KB_ù, KB_², KB_LSHIFT, '*', 'w', 'x', 'c', 'v', 
    'b', 'n', ',', ';', ':', '!', KB_RSHIFT, '*', KB_ALT, ' ', KB_CAPS_LOCK, KB_F1, KB_F2, KB_F3, KB_F4, KB_F5, 
    KB_F6, KB_F7, KB_F8, KB_F9, KB_F10, KB_NUMLOCK, KB_SCROLLLOCK, KB_NUMPAD_7, KB_NUMPAD_8, KB_NUMPAD_9, '-', KB_NUMPAD_4, KB_NUMPAD_5, KB_NUMPAD_6, '+', KB_NUMPAD_1, 
    KB_NUMPAD_2, KB_NUMPAD_3, KB_NUMPAD_0, '.', 0, 0, '<', KB_F11, KB_F12, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};	

uint16_t kb_azerty_set2_caps[128] =
{
    0,  KB_ESCAPE, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', KB_DEGREE, '+', '\b', '\t', 
    'A', 'Z', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 0, KB_POUND, '\n', KB_LCTRL, 'Q', 'S', 
    'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', '%', 0, KB_LSHIFT, KB_µ, 'W', 'X', 'C', 'V', 
    'B', 'N', '?', '.', '/', KB_SECTION, KB_RSHIFT, '*', KB_ALT, ' ', KB_CAPS_LOCK, KB_F1, KB_F2, KB_F3, KB_F4, KB_F5, 
    KB_F6, KB_F7, KB_F8, KB_F9, KB_F10, KB_NUMLOCK, KB_SCROLLLOCK, KB_NUMPAD_7, KB_NUMPAD_8, KB_NUMPAD_9, '-', KB_NUMPAD_4, KB_NUMPAD_5, KB_NUMPAD_6, '+', KB_NUMPAD_1, 
    KB_NUMPAD_2, KB_NUMPAD_3, KB_NUMPAD_0, KB_DELETE, 0, 0, '>', KB_F11, KB_F12, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};	

uint16_t kb_azerty_set2_altgr[128] = 
{
    0,  0, 0, '~', '#', '{', '[', '|', '`', '\\', '^', '@', ']', '}', '\b', '\t', 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, KB_CAPS_LOCK, KB_F1, KB_F2, KB_F3, KB_F4, KB_F5, 
    KB_F6, KB_F7, KB_F8, KB_F9, KB_F10, KB_NUMLOCK, KB_SCROLLLOCK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, KB_F11, KB_F12, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

uint16_t kb_azerty_set2_extended[128] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '\n', KB_RCTRL, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, '/', 0, 0, KB_ALT_GR, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, KB_UP, 0, 0, KB_LEFT, 0, KB_RIGHT, 0, 0, 
    KB_DOWN, 0, 0, KB_DELETE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

bool kb_state[128] = { false }, kb_state_extended[128] = { false };

enum KB_LAYOUT
{
    //KB_QWERTY,
    KB_AZERTY
};

bool kb_capsLock = false, kb_numLock = false, kb_scrollLock = false;
enum KB_LAYOUT kb_layout = KB_AZERTY;
bool kb_extendedScancode = false;

void PS2_KB_Init()
{
    memset(&kb_state, false, 128);
}

bool PS2_KB_ResetKeyboard()
{
	PS2_Wait();
	outb(PS2_DATA_PORT, 0xff);
    io_wait();
	if(inb(PS2_DATA_PORT) == KB_RESEND)
		return PS2_KB_ResetKeyboard();
	return (inb(PS2_DATA_PORT) == 0xaa);
}

void PS2_KB_SetScancodeSet(uint8_t set)
{
	PS2_Wait();
	outb(PS2_DATA_PORT, 0xf0);
    io_wait();
	outb(PS2_DATA_PORT, set);
    io_wait();
	if(inb(PS2_DATA_PORT) == KB_RESEND)
		PS2_KB_SetScancodeSet(set);
}

uint8_t PS2_KB_GetScancodeSet()
{
	PS2_Wait();
	outb(PS2_DATA_PORT, 0xf0);
    io_wait();
	outb(PS2_DATA_PORT, 0);
	if(inb(PS2_DATA_PORT) == KB_RESEND)
		return PS2_KB_GetScancodeSet();
	uint8_t r = inb(PS2_DATA_PORT);
	return r == 0x43 ? KB_SCANCODE_SET_1 : (r == 0x41 ? KB_SCANCODE_SET_2 : KB_SCANCODE_SET_3 /*3f*/);
}

void PS2_KB_SetScancodeKeyState(uint8_t scancode, bool extended, bool state)
{
    if(extended)
        kb_state_extended[scancode] = state;
    else
        kb_state[scancode] = state;
}

bool PS2_KB_GetScancodeKeyState(uint8_t scancode, bool extended)
{
    if(extended)
        return kb_state_extended[scancode];
    else
        return kb_state[scancode];
}

void PS2_KB_SetKeyState(uint16_t key, bool state)
{
	for(uint8_t i = 0; i < 128; i++)
	{
        if(kb_layout == KB_AZERTY)
        {
            if(kb_azerty_set2[i] == key)
                PS2_KB_SetScancodeKeyState(i, false, state);
        }
        // else if(kb_layout == KB_QWERTY)
        // {
        //     if(kb_qwerty_set2[i] == key)
        //         PS2_KB_SetScancodeKeyState(i, false, state);
        // }
	}

    for(uint8_t i = 0; i < 128; i++)
	{
        if(kb_layout == KB_AZERTY)
        {
            if(kb_azerty_set2_extended[i] == key)
                PS2_KB_SetScancodeKeyState(i, true, state);
        }
        // else if(kb_layout == KB_QWERTY)
        // {
        //     if(kb_qwerty_set2_extended[i] == key)
        //         PS2_KB_SetScancodeKeyState(i, true, state);
        // }
	}
}

bool PS2_KB_GetKeyState(uint16_t key)
{
	bool r = false;
	for(uint8_t i = 0; i < 128; i++)
	{
		if(kb_layout == KB_AZERTY)
        {
            if(kb_azerty_set2[i] == key)
                r |= PS2_KB_GetScancodeKeyState(i, false);
        }
        // else if(kb_layout == KB_QWERTY)
        // {
        //     if(kb_qwerty_set2[i] == key)
        //         r |= PS2_KB_GetScancodeKeyState(i, false);
        // }
	}

    for(uint8_t i = 0; i < 128; i++)
	{
		if(kb_layout == KB_AZERTY)
        {
            if(kb_azerty_set2_extended[i] == key)
                r |= PS2_KB_GetScancodeKeyState(i, true);
        }
        // else if(kb_layout == KB_QWERTY)
        // {
        //     if(kb_qwerty_set2_extended[i] == key)
        //         r |= PS2_KB_GetScancodeKeyState(i, true);
        // }
	}

	return r;
}

uint16_t PS2_KB_GetKey(uint8_t scancode, bool extended)
{
    if(kb_layout == KB_AZERTY)
    {
        if(extended)
            return kb_azerty_set2_extended[scancode];
        return kb_azerty_set2[scancode];
    }
    return 0;
}

uint16_t PS2_KB_GetFormattedKey(uint8_t scancode, bool extended)
{
    if(kb_layout == KB_AZERTY)
    {
        if(extended)
            return kb_azerty_set2_extended[scancode];
        if(kb_capsLock ^ (PS2_KB_GetKeyState(KB_LSHIFT) || PS2_KB_GetKeyState(KB_RSHIFT)))
        {
            if(PS2_KB_GetKeyState(KB_ALT_GR))
                return 0;
            return kb_azerty_set2_caps[scancode];
        }
        else
        {
            if(PS2_KB_GetKeyState(KB_ALT_GR))
                return kb_azerty_set2_altgr[scancode];
            return kb_azerty_set2[scancode];
        }
    }
    return 0;
}

bool PS2_KB_AnyKeyPressed()
{
    for(uint8_t i = 0; i < 128; i++)
        if(PS2_KB_GetScancodeKeyState(i, false)) return true;
    for(uint8_t i = 0; i < 128; i++)
        if(PS2_KB_GetScancodeKeyState(i, true)) return true;
    return false;
}

void HandleIRQ1()
{
    uint8_t scancode = inb(PS2_DATA_PORT);

    if(scancode == 0xe0)
    {
        kb_extendedScancode = true;
        return;
    }

    if(scancode >> 7)   // Key released
        PS2_KB_SetScancodeKeyState(scancode - 0x80, kb_extendedScancode, false);
    else                // Key pressed
    {
        uint16_t key = PS2_KB_GetKey(scancode, kb_extendedScancode);
        PS2_KB_SetScancodeKeyState(scancode, kb_extendedScancode, true);
        if(key == KB_CAPS_LOCK)
        {
            kb_capsLock ^= 1;
            // PS2_KB_SetLEDState(KB_LED_CAPS_LOCK * kb_capsLock);
        }
        else if(key == KB_NUMLOCK)
            kb_numLock ^= 1;
        else if(key == KB_SCROLLLOCK)
            kb_scrollLock ^= 1;
        // else if(key == (key & 0xff) || (kb_numLock && (key == KB_NUMPAD_1 || key == KB_NUMPAD_2 || key == KB_NUMPAD_3 || 
        //                                                key == KB_NUMPAD_4 || key == KB_NUMPAD_5 || key == KB_NUMPAD_6 || 
        //                                                key == KB_NUMPAD_7 || key == KB_NUMPAD_8 || key == KB_NUMPAD_9 || 
        //                                                key == KB_NUMPAD_0)))
        // {
        //     kb_text_key = scancode;
        //     kb_text_key_extended = kb_extendedScancode;
        //     kb_text_key_pressed = true;
        // }
    }

    kb_extendedScancode = false;
}