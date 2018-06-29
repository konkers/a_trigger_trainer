#ifndef __MEMPAGES_H__
#define __MEMPAGES_H__

#include <stdint.h>

extern uint8_t NMI_flag;
#pragma zpsym ("NMI_flag")

extern uint8_t Frame_Count;
#pragma zpsym ("Frame_Count")

extern uint8_t index;
#pragma zpsym ("index")

extern uint8_t index4;
#pragma zpsym ("index4")

extern uint8_t X1;
#pragma zpsym ("X1")

extern uint8_t Y1;
#pragma zpsym ("Y1")

extern uint8_t state;
#pragma zpsym ("state")

extern uint8_t state4;
#pragma zpsym ("state4")

extern uint8_t joypad1;
#pragma zpsym ("joypad1")

extern uint8_t joypad1old;
#pragma zpsym ("joypad1old")

extern uint8_t joypad1test; 
#pragma zpsym ("joypad1test")

extern uint8_t joypad2; 
#pragma zpsym ("joypad2")

extern uint8_t joypad2old;
#pragma zpsym ("joypad2old")

extern uint8_t joypad2test;
#pragma zpsym ("joypad2test")

extern uint8_t zip_state;
#pragma zpsym ("zip_state")

extern uint8_t zip_frames;
#pragma zpsym ("zip_frames")

extern uint8_t zip_dig0;
#pragma zpsym ("zip_dig0")

extern uint8_t zip_dig1;
#pragma zpsym ("zip_dig1")

extern uint8_t zip_dig2;
#pragma zpsym ("zip_dig2")

extern uint8_t bg_color;
#pragma zpsym ("bg_color")


#pragma bss-name(push, "OAM")
extern uint8_t SPRITES[256];
#endif  // __MEMPAGES_H__
