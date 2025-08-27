#ifndef RENDER_INTERNAL_H
# define RENDER_INTERNAL_H

# include <SDL2/SDL.h>

# include "../types.h"
# include "render.h"

typedef struct render_state_internal
{
	u32	vao_quad; // vertex array object - instructions on how to access the object data
	u32	vbo_quad; // vertex buffer object - object data itself
	u32	ebo_quad; // element buffer object - indices of the vertex array buffer
}	Render_State_Internal;

SDL_Window	*render_init_window(u32 width, u32 height);
void		render_init_quad(u32 *vao, u32 *vbo, u32 *ebo);

#endif
