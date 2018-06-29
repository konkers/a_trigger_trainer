#include "mem_pages.h"
// Globals
// our startup code initialized all values to zero
#pragma bss-name(push, "ZEROPAGE")
uint8_t NMI_flag;
uint8_t Frame_Count;
uint8_t index;
uint8_t index4;
uint8_t X1;
uint8_t Y1;
uint8_t state;
uint8_t state4;
uint8_t joypad1;
uint8_t joypad1old;
uint8_t joypad1test; 
uint8_t joypad2; 
uint8_t joypad2old;
uint8_t joypad2test;
uint8_t zip_state;
uint8_t zip_frames;
uint8_t zip_dig0;
uint8_t zip_dig1;
uint8_t zip_dig2;
uint8_t bg_color;

#pragma bss-name(push, "OAM")
uint8_t SPRITES[256];
// OAM equals ram addresses 200-2ff
