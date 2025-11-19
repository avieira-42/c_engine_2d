#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "engine/glad.h"
#include "engine/global.h"
#include "engine/config.h"
#include "engine/input.h"
#include "engine/time.h"
#include "engine/physics.h"
#include "engine/util.h"

#define	SDL_MAIN_HANDLED

static bool	should_quit = true;
static vec2 pos;

static	void	input_handle(void)
{
	// USER_INPUT SET
	/*if (global.input.left == KS_PRESSED || global.input.left == KS_HELD
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
	}*/

	i32	x, y;

	SDL_GetMouseState(&x, &y);
	pos[0] = (f32)x;
	pos[1] = global.render.height - y;
}

int	main(void)
{
	time_init(60);
	config_init();
	render_init();
	physics_init();


	// GENERATE RANDOM BODIES
	/*
	u32		i;
	u32		body_count;
	body_count = 100;
	Body	*body;
	usize	body_index;
	 * for(i = 0; i < body_count; ++i)
	{
		body_index = physics_body_create(
				(vec2) { rand() % (i32)global.render.width, rand() % (i32)global.render.height},
				(vec2) { rand() % 100, rand() % 100 });
		body = physics_body_get(body_index);
		body->acceleration[0] = rand() % 200 - 100;
		body->acceleration[1] = rand() % 200 - 100;
	}*/


	pos[0] = global.render.width * 0.5;
	pos[1] = global.render.height * 0.5;

	SDL_ShowCursor(false);

	// TEST COLLISIONS
	AABB test_aabb = 
	{
		.position = {global.render.width * 0.5, global.render.height * 0.5},
		.half_size = {50, 50}
	};

	AABB cursor_aabb = {.half_size = {75, 75}};

	AABB start_aabb = {.half_size = {75, 75}};

	vec2 start_aabb_point = {1, 1};

	AABB sum_aabb =
	{
		.position = {test_aabb.position[0], test_aabb.position[1]},
		.half_size =
		{
			test_aabb.half_size[0] + cursor_aabb.half_size[0],
			test_aabb.half_size[1] + cursor_aabb.half_size[1]
		}
	};

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
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						start_aabb.position[0] = pos[0];
						start_aabb.position[1] = pos[1];
						start_aabb_point[0] = pos[0];
						start_aabb_point[1] = pos[1];
					}
				default:
					break;
			}
		}

		input_update();
		input_handle();
		physics_update();

		render_begin();

		cursor_aabb.position[0] = pos[0];
		cursor_aabb.position[1] = pos[1];

		render_aabb((f32 *)&test_aabb, WHITE);

		render_aabb((f32 *)&sum_aabb, FADED);

		render_aabb((f32 *)&cursor_aabb, WHITE);

		render_quad(start_aabb_point, (vec2){5, 5}, FADED);

		if (physics_aabb_intersect_aabb(test_aabb, cursor_aabb))
			render_aabb((f32 *)&cursor_aabb, RED);
		else
			render_aabb((f32 *)&cursor_aabb, WHITE);

		if (physics_point_intersect_aabb(pos, test_aabb))
			render_quad(pos, (vec2){5, 5}, RED);
		else
			render_quad(pos, (vec2){5, 5}, CYAN);

		render_aabb((f32 *)&start_aabb, FADED);
		render_line_segment(start_aabb.position, pos, FADED);

		f32	x = sum_aabb.position[0];
		f32	y = sum_aabb.position[1];
		f32	size = sum_aabb.half_size[0];

		render_line_segment((vec2){x - size, 0}, (vec2){x - size, global.render.height}, FADED);
		render_line_segment((vec2){x + size, 0}, (vec2){x + size, global.render.height}, FADED);
		render_line_segment((vec2){0, y - size}, (vec2){global.render.width, y - size}, FADED);
		render_line_segment((vec2){0, y + size}, (vec2){global.render.width, y + size}, FADED);

		vec2	min, max;
		aabb_min_max(min, max, sum_aabb);

		vec2	magnitude;
		vec2_sub(magnitude, pos, start_aabb.position);

		Hit	hit = ray_intersect_aabb(start_aabb.position, magnitude, sum_aabb);

		if (hit.is_hit)
		{
			AABB	hit_aabb = 
			{
				.position = {hit.position[0], hit.position[1]},
				.half_size = {start_aabb.half_size[0], start_aabb.half_size[1]}
			};
			render_aabb((f32 *)&hit_aabb, CYAN);
			render_quad(hit.position, (vec2){5, 5}, CYAN);
		}

		for (u8 i = 0; i < 2; ++i)
		{
			if (magnitude[i] != 0)
			{
				f32	t1 = (min[i] - pos[i]) / magnitude[i];
				f32	t2 = (max[i] - pos[i]) / magnitude[i];

				vec2	point;
				vec2_scale(point, magnitude, t1);
				vec2_add(point, point, pos);
				if (min[i] < start_aabb.position[i])
					render_quad(point, (vec2){5,5}, ORANGE);
				else
					render_quad(point, (vec2){5,5}, CYAN);

				vec2_scale(point, magnitude, t2);
				vec2_add(point, point, pos);
				if (max[i] < start_aabb.position[i])
					render_quad(point, (vec2){5,5}, CYAN);
				else
					render_quad(point, (vec2){5, 5}, ORANGE);
			}
		}

		render_end();
		time_update_late();
	}
	return (0);
}
