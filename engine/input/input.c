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

    /*update_key_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_KEY_LEFT]),
                &global.input.left);
    update_key_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_KEY_RIGHT]),
                &global.input.right);
    update_key_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_KEY_UP]),
				&global.input.up);
    update_key_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_KEY_DOWN]),
                &global.input.down);
    update_key_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_KEY_ESCAPE]),
                &global.input.escape);*/

    update_pad_state(SDL_GameControllerGetButton(gamepad,
				global.config.padbinds[INPUT_DPAD_LEFT]),
                &global.input.dpad_left);
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
