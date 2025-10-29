#include "../util.h"
#include "../global/global.h"
#include "../../../include/glad/glad.h"

#include <SDL2/SDL.h>


#include "render.h"
#include "render_internal.h"

SDL_Window *render_init_window(u32 width, u32 height)
{
	(void) width;
	(void) height;
	SDL_Window *window;

	// OpenGL uses Core Profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// OpenGl version used is 3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	// OpenGL sub_version used is 0.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);


	// Init SDL Video
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ERROR_EXIT("Could not init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	// Set Window Specifications
	window = SDL_CreateWindow
		(
		 "MyGame",
		 SDL_WINDOWPOS_CENTERED,
		 SDL_WINDOWPOS_CENTERED,
		 800,
		 600,
		 SDL_WINDOW_OPENGL
		);

	if (!window)
	{
		ERROR_EXIT("Failed to init window:%s\n", SDL_GetError());
		exit(1);
	}

	// Create the OpenGL context addociated with window
	SDL_GL_CreateContext(window);

	// Load OpenGl functions and get their addresses from the GPU drivers
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		ERROR_EXIT("Failed to load GL: %s\n", SDL_GetError());
		exit(1);
	}

	puts("OpenGL Loaded");

	// Get the Vendor, the Renderer and the Version of the OpenGl context
	printf("Vendor:		%s\n", glGetString(GL_VENDOR));
	printf("Renderer:	%s\n", glGetString(GL_RENDERER));
	printf("Version:	%s\n", glGetString(GL_VERSION));

	return window;
}

void	render_init_shaders(Render_State_Internal *state)
{
	state->shader_default = render_shader_create("srcs/shaders/default.vert", "srcs/shaders/default.frag");

	mat4x4_ortho(state->projection, 0, global.render.width, 0, global.render.height, -2, 2);

	glUseProgram(state->shader_default);
	glUniformMatrix4fv
		(
		 glGetUniformLocation(state->shader_default, "projection"),
		 1,
		 GL_FALSE,
		 &state->projection[0][0]
		);
}

void	render_init_color_texture(u32 *texture)
{
	u8	solid_white[4];

	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	
	solid_white[0] = 255;
	solid_white[1] = 255;
	solid_white[2] = 255;
	solid_white[3] = 255;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, solid_white);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void	render_init_quad(u32 *vao, u32 *vbo, u32 *ebo)
{
	/* Set vertices coordinates (x, y, z) and  texture coordinates (u = horizontal, v = vertical)
	 x y z tell which part of a 3d image is and
	 u v tell which part of a 2d image should be placed on the respective vertice */
	f32 vertices[] = 
	{
		 0.5,  0.5, 0, 0, 0, // vertice 0
		 0.5, -0.5, 0, 0, 1, // vertice 1
		-0.5, -0.5, 0, 1, 1, // vertice 2
		-0.5,  0.5, 0, 1, 0  // vertice 3
	};

	// Set which vertices to draw each of the 2 triangles to make a quad
	u32 indices[] = // vertice : 0, 1 , 2 and 3
	{
		0, 1, 3, // triangle 0
		1, 2, 3  // trianlge 1
	};

	// Generate the handles to the object to draw
	glGenVertexArrays(1, vao); // Generate 1 VAO
	glGenBuffers(1, vbo); // Generate 1 VBO
	glGenBuffers(1, ebo); // Gnerate 1 EBO

	/* Bind objects to OpenGL context, stating that all subsequent  vertex attribute
	conficuration calls affect that VAO until another is bound or this one is unbound */
	glBindVertexArray(*vao); // Bind VAO

	glBindBuffer(GL_ARRAY_BUFFER, *vbo); // Bind VBO to GL_ARRAY_BUFFER for future use according to VAO instructions
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Populate VBO with data

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo); // Bind EBO to GL_ELEMENT_ARRAY_BUFFER and chain it directly to VAO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // Populate EBO with data

	/* xyz Link VBO to VAO:
	 Use the first 3 elements of size f32 since the index 0 then continue
	 after 5 f32 sized elements counting from the first */
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 5 *sizeof(f32), NULL);
	// OpenGl use a vertix attribute during rendering
	glEnableVertexAttribArray(0);

	/* uv Link VBO to VAO
	 Use the first 2 elments of size f32 since the index 1 then continue
	 after 5 f32 sized elements counting from the first one */
	glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)(3 * sizeof(f32)));
	// OpenGl use a vertix attribute during rendering
	glad_glEnableVertexAttribArray(1);

	// Unbound the VAO
	glBindVertexArray(0);
}
