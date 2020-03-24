// #ifndef INPUT_H
// #define INPUT_H

#include <genesis.h>

extern bool btn_A;
extern bool btn_B;
extern bool btn_C;
extern bool btn_Up;
extern bool btn_Down;
extern bool btn_Left;
extern bool btn_Right;
extern bool btn_Start;
extern bool btndown_A;
extern bool btndown_B;
extern bool btndown_C;
extern bool btndown_Up;
extern bool btndown_Down;
extern bool btndown_Left;
extern bool btndown_Right;
extern bool btndown_Start;
extern bool btnup_A;
extern bool btnup_B;
extern bool btnup_C;
extern bool btnup_Up;
extern bool btnup_Down;
extern bool btnup_Left;
extern bool btnup_Right;
extern bool btnup_Start;

extern bool btn_X;
extern bool btn_Y;
extern bool btn_Z;
extern bool btndown_X;
extern bool btndown_Y;
extern bool btndown_Z;
extern bool btnup_X;
extern bool btnup_Y;
extern bool btnup_Z;


void InputHandler( u16 joy, u16 changed, u16 state);
void ResetInputFlags();


//#endif