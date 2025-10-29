#pragma once

typedef enum input_key
{
	INPUT_KEY_LEFT,
	INPUT_KEY_RIGHT,
	INPUT_KEY_UP,
	INPUT_KEY_DOWN,
	INPUT_KEY_ESCAPE,
}	Input_key;

typedef enum key_state
{
	KS_UNPRESSED,
	KS_PRESSED,
	KS_HELD,
}	Key_state;

typedef struct input_state
{
	Key_state	left;
	Key_state	right;
	Key_state	up;
	Key_state	down;
	Key_state	escape;
} Input_state;

void	input_update(void);
