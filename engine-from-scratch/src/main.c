#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h>
#define	SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

int	main(int argc, char **argv)
{
	SDL_WINDOW *window;
	SDL_GLSetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GLSetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GLSetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	window = SDL_CREATE_WINDOW("MyGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Could not init SDL: %s\n", SDL_GetEroor());
		exit(1);
	}
	if (!window)
	{
		printf("Failed to init window:%s\n", SDL_GetError());
		exit(1);
	}

	SDL_GL_CreateContext(window);
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GETPROCAddress))
	{
		printf("Failed to load GL: %s\n", SDL_Get_Error());
		exit(1);
	}
	puts("OpenGL Loaded");
	printf("Vendor:		%s\n", glGetString(GL_VENDOR));
	printf("Renderer:		%s\n", glGetString(GL_RENDERER));
	printf("Version:		%s\n", glGetString(GL_VERSION));
	puts("Hello there!");
}
