#include <stdbool.h>
#include <SDL2/SDL.h>

#include "engine/glad.h"
#include "engine/global.h"
#include "engine/config.h"
#include "engine/input.h"
#include "engine/time.h"

#define	SDL_MAIN_HANDLED

static bool	should_quit = true;
static vec2 pos;

static	void	input_handle(void)
{
	if (global.input.left == KS_PRESSED || global.input.left == KS_HELD
		|| global.input.dpad_left == KS_PRESSED || global.input.dpad_left == KS_HELD)
	{
		pos[0] = pos[0] - 500 * global.time.delta;
	}
	if (global.input.right == KS_PRESSED || global.input.right == KS_HELD
		|| global.input.dpad_right == KS_PRESSED || global.input.dpad_right == KS_HELD)
	{
		pos[0] = pos[0] + 500 * global.time.delta;
	}
	if (global.input.down == KS_PRESSED || global.input.down == KS_HELD
		|| global.input.dpad_down == KS_PRESSED || global.input.dpad_down == KS_HELD)
	{
		pos[1] = pos[1] - 500 * global.time.delta;
	}
	if (global.input.up == KS_PRESSED || global.input.up == KS_HELD
		|| global.input.dpad_up == KS_PRESSED || global.input.dpad_up == KS_HELD)
	{
		pos[1] = pos[1] + 500 * global.time.delta;
	}
	if (global.input.escape == KS_PRESSED || global.input.escape == KS_HELD)
	{
		should_quit = true;
	}
}

int	main(void)
{
	time_init(60);
	config_init();
	render_init();

	pos[0] = global.render.width * 0.5;
	pos[1] = global.render.height * 0.5;

	should_quit = false;
	while (!should_quit)
	{
		time_update();
		SDL_Event event;
		// Checks if the event is pending or not
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				// When user clicks on window X (event.type == SDL_QUIT)
				case SDL_QUIT:
					should_quit = true;
					break;
				default:
					break;
			}
		}

		input_update();
		input_handle();

		render_begin();

		render_quad(pos, (vec2){50, 50}, (vec4){0, 1, 0, 1});

		render_end();
		time_update_late();
	}

	return (0);
}
