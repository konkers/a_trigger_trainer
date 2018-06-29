#include "asm4c.h"
#include "mem_pages.h"
#include "nes.h"

void PPU_Update(void);


#define NT_ADDR(num, x, y) (0x2000 + (0x400 * (num)) + (x) + ((y) * 32))
#define NT_ADDR_HIGH(num, x, y) (NT_ADDR(num, x, y) >> 8)
#define NT_ADDR_LOW(num, x, y) (NT_ADDR(num, x, y) & 0xff)

#define WRITE_TEXT_CENTER(y, text) do {\
	write_text((32 - sizeof(text))/2, y, (text));\
} while(0)

#define ZIP_STATE_IDLE 0
#define ZIP_STATE_WAIT 1

const unsigned char PALETTE[]={
0x15, 0x1f, 0x20, 1,
0x15, 0x37, 0x24, 1,
0x15, 0x37, 0x24, 1,
0x15, 0x37, 0x24, 1,
0x15, 0x37, 0x24, 1,
0x15, 0x37, 0x24, 1,
0x15, 0x37, 0x24, 1,
0x15, 0x37, 0x24, 1,
};

void move_logic(void)
{
	switch (zip_state)
	{
		case ZIP_STATE_IDLE : if ((joypad1 & A_BUTTON) && !(joypad1old & A_BUTTON))
		{
			zip_state = ZIP_STATE_WAIT;
			zip_frames = 0;
		}
		break;
	case ZIP_STATE_WAIT:
		zip_frames++;
		if ((joypad1 & LEFT) && !(joypad1old & LEFT))
		{
			zip_state = ZIP_STATE_IDLE;
			if (zip_frames >= 3 && zip_frames <= 6) {
				bg_color = 0x1a;
			} else {
				bg_color = 0x15;
			}
		}
		break;
	}
}


void all_off(void)
{
	PPU_CTRL = 0;
	PPU_MASK = 0;
}

void all_on(void)
{
	PPU_CTRL = 0x90; // screen is on, NMI on
	PPU_MASK = 0x1e;
}

void reset_scroll(void)
{
	PPU_ADDRESS = 0;
	PPU_ADDRESS = 0;
	SCROLL = 0;
	SCROLL = 0;
}

void load_palette(void)
{
	PPU_ADDRESS = 0x3f;
	PPU_ADDRESS = 0x00;
	for (index = 0; index < sizeof(PALETTE); ++index)
	{
		PPU_DATA = PALETTE[index];
	}
}

void write_text(uint8_t x, uint8_t y, const unsigned char *str) {
	PPU_ADDRESS = NT_ADDR_HIGH(0, x, y);
	PPU_ADDRESS = NT_ADDR_LOW(0, x, y);
	while (*str) {
		PPU_DATA = *str;//0x30;//*str + 0x20 - ' ';
		str++;
	}
}

void ppu_update(void)
{
	PPU_ADDRESS = NT_ADDR_HIGH(0, 18, 14);
	PPU_ADDRESS = NT_ADDR_LOW(0, 18, 14);
	PPU_DATA = zip_dig2;
	PPU_DATA = zip_dig1;
	PPU_DATA = zip_dig0;

	PPU_ADDRESS = 0x3f;
	PPU_ADDRESS = 0x00;
	PPU_DATA = bg_color;

	reset_scroll();
}


void main(void)
{
	all_off(); // turn off screen
	X1 = 0x7f; // set the starting position of the top left sprite
	Y1 = 0x77; // middle of screen

	load_palette();

	WRITE_TEXT_CENTER(6, "A TRIGGER TRAINER");

	WRITE_TEXT_CENTER(9, "by KONKERS");
	WRITE_TEXT_CENTER(10, "(twitch.tv/djkonkers)");

	write_text(10, 14, "Frames:");
	write_text(4, 18, "Help:");
	write_text(6, 19, "press A then LEFT");
	write_text(6, 20, "3-6 frames? Winner!");


	reset_scroll();

	bg_color = 0x1f;
	all_on(); // turn on screen

	while (1)
	{
		uint8_t tmp_frames;
		while (NMI_flag == 0)
			; // wait till NMI

		ppu_update();
		read_input();
		move_logic();

		tmp_frames = zip_frames;

		zip_dig0 = '0' + (tmp_frames % 10);
		tmp_frames /= 10;
		zip_dig1 = '0' + (tmp_frames % 10);
		tmp_frames /= 10;
		zip_dig2 = '0' + (tmp_frames % 10);
		NMI_flag = 0;
	}
}
