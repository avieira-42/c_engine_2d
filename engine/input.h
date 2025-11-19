#pragma once

typedef enum input_key
{
	INPUT_KEY_LEFT,
	INPUT_KEY_RIGHT,
	INPUT_KEY_UP,
	INPUT_KEY_DOWN,
	INPUT_KEY_ESCAPE,
}	Input_Key;

typedef enum input_pad
{
	INPUT_DPAD_LEFT,
	INPUT_DPAD_RIGHT,
	INPUT_DPAD_UP,
	INPUT_DPAD_DOWN,
	INPUT_L_JOYSTICK_LEFT,
	INPUT_L_JOYSTICK_RIGHT,
	INPUT_L_JOYSTICK_UP,
	INPUT_L_JOYSTICK_DOWN,
	INPUT_R_JOYSTICK_LEFT,
	INPUT_R_JOYSTICK_RIGHT,
	INPUT_R_JOYSTICK_UP,
	INPUT_R_JOYSTICK_DOWN,
	INPUT_R,
	INPUT_R1,
	INPUT_R2,
	INPUT_L,
	INPUT_L1,
	INPUT_L2,
	INPUT_CROSS,
	INPUT_SQUARE,
	INPUT_CIRCLE,
	INPUT_TRIANGLE,
	INPUT_SELECT,
	INPUT_OPTIONS,
	INPUT_HOME,
	INPUT_TOUCH,
	INPUT_GUIDE,
}	Input_Pad;

typedef enum key_state
{
	KS_UNPRESSED,
	KS_PRESSED,
	KS_HELD,
}	Key_State;

typedef struct input_state
{
	Key_State	left;
	Key_State	right;
	Key_State	up;
	Key_State	down;
	Key_State	escape;
	Key_State	dpad_left;
	Key_State	dpad_right;
	Key_State	dpad_up;
	Key_State	dpad_down;
	Key_State	joystick_left;
	Key_State	joystick_right;
	Key_State	joystick_up;
	Key_State	joystick_down;
	Key_State	cross;
	Key_State	square;
	Key_State	circle;
	Key_State	triangle;
	Key_State	r;
	Key_State	r1;
	Key_State	r2;
	Key_State	l;
	Key_State	l1;
	Key_State	l2;
	Key_State	options;
	Key_State	start;
	Key_State	home;
	Key_State	touch;
} Input_State;

void	input_update(void);
