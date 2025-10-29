#include "engine/global/global.h"
#include "../include/glad/glad.h"

#include <stdbool.h>
#include <SDL2/SDL.h>

#define	SDL_MAIN_HANDLED

int	main(void)
{
	bool	should_quit;

	render_init();

	should_quit = false;
	while (!should_quit)
	{
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

		render_begin();

		render_quad
			(
			 (vec2){global.render.width * 0.5, global.render.height * 0.5},
			 (vec2){50, 50},
			 (vec4){0, 1, 0, 1}
			);

		render_end();
	}

	return (0);
}
