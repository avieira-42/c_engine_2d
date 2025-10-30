#include "../glad.h"
#include "../global.h"
#include "../render.h"
#include "render_internal.h"

static Render_State_Internal state = {0};

void	render_init(void)
{
	// Assign screen width and height
	global.render.width = 800;
	global.render.height = 600;
	global.render.window = render_init_window(global.render.width, global.render.height);

	// Assign quad data to OpenGl context
	render_init_quad(&state.vao_quad, &state.vbo_quad, &state.ebo_quad);

	render_init_shaders(&state);
	render_init_color_texture(&state.texture_color);
}

void	render_begin(void)
{
	// Set background color before drawing
	glClearColor(0.08, 0.1, 0.1, 1);

	// Clear the color buffer (3 buffers = color, depth and stencil)
	glClear(GL_COLOR_BUFFER_BIT);
}

void	render_end(void)
{
	// Update window
	SDL_GL_SwapWindow(global.render.window);
}

void	render_quad(vec2 pos, vec2 size, vec4 color)
{
	mat4x4	model;

	glUseProgram(state.shader_default);

	mat4x4_identity(model);

	mat4x4_translate(model, pos[0], pos[1], 0);
	mat4x4_scale_aniso(model, model, size[0], size[1], 1);

	glUniformMatrix4fv(glGetUniformLocation(state.shader_default, "model"), 1, GL_FALSE, &model[0][0]);
	glUniform4fv(glad_glGetUniformLocation(state.shader_default, "color"), 1, color);

	// Bind VAO to OpenGL context
	glBindVertexArray(state.vao_quad);

	// Draw the front and back lines of the polygons -> glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindTexture(GL_TEXTURE_2D, state.texture_color);
	// Tell OpenGL that we want to use 6 elements (in this case being 6 indeces from the EBO)
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

	glBindVertexArray(0);
}
