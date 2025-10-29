CC = cc

FLAGS = -Wall -Wextra -Werror -g

LIBS = -lm `sdl2-config --cflags --libs` -lSDL2_mixer `pkg-config --libs glfw3` -ldl

GLAD = include/glad/glad.c

RENDER = srcs/engine/render/render.c \
		 srcs/engine/render/render_init.c \
		 srcs/engine/render/render_utils.c

IO = srcs/engine/io/io.c

GLOBAL = srcs/engine/global/global.c

MAIN = srcs/main.c

ENGINE = $(GLOBAL) \
		 $(IO) \
		 $(RENDER) \
		 $(GLAD)

SRCS = $(MAIN) \
	   $(ENGINE)

game: $(SRCS)
	$(CC) $(FLAGS) $(SRCS) $(LIBS) -o game

clean:
	rm -rf game

re: clean game
