#include <stdbool.h>

#include "../input.h"
#include "../types.h"
#include "../global.h"

SDL_GameController	*gamepad;

static void	update_key_state(u8 current_state, Key_State *key_state)
{
	if (current_state != 0)
	{
		if (*key_state > 0)
			*key_state = KS_HELD;
		else
			*key_state = KS_PRESSED;
	}
	else
		*key_state = KS_UNPRESSED;
}

static void	update_pad_state(u8 current_state, Key_State *pad_state)
{
	if (current_state != 0)
	{
		if (*pad_state > 0)
			*pad_state = KS_HELD;
		else
			*pad_state = KS_PRESSED;
	}
	else
		*pad_state = KS_UNPRESSED;
}

static bool	gamepad_load(void)
{
	int					gamepad_index;
	int					gamepad_count;

	gamepad_count = SDL_NumJoysticks();

	gamepad_index = 0;
	while (gamepad_count--)
	{
		if (SDL_IsGameController(gamepad_index) == true)
		{
			gamepad = SDL_GameControllerOpen(gamepad_index);
			return (true);
		}
	}
	return (false);
}

static void	input_gamepad_update(void)
{
	if (gamepad_load() == false)
		return ;

    update_key_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_DPAD_RIGHT]),
                &global.input.dpad_right);
    update_key_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_DPAD_UP]),
				&global.input.dpad_up);
    update_key_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_DPAD_DOWN]),
                &global.input.dpad_down);
    update_pad_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_DPAD_LEFT]),
                &global.input.dpad_left);
    update_pad_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_R]),
                &global.input.r);
    update_pad_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_R1]),
                &global.input.r1);
    update_pad_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_R2]),
                &global.input.r2);
    update_pad_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_L]),
                &global.input.l);
    update_pad_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_L1]),
                &global.input.l1);
    update_pad_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_L2]),
                &global.input.l2);
    update_pad_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_CROSS]),
                &global.input.cross);
    update_pad_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_CIRCLE]),
                &global.input.circle);
    update_pad_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_SQUARE]),
                &global.input.square);
    update_pad_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_TRIANGLE]),
                &global.input.triangle);
    update_pad_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_HOME]),
                &global.input.home);
} 

static void	input_keyboard_update(void)
{
	const u8	*keyboard_state;

	keyboard_state = SDL_GetKeyboardState(NULL);

	update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_LEFT]], &global.input.left);
	update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_RIGHT]], &global.input.right);
	update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_UP]], &global.input.up);
	update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_DOWN]], &global.input.down);
	update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_ESCAPE]], &global.input.escape);
}

void	input_update(void)
{
	input_keyboard_update();
	input_gamepad_update();
}
