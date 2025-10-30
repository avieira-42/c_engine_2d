CC = cc

FLAGS = -Wall -Wextra -Werror -g

LIBS = -lm `sdl2-config --cflags --libs` -lSDL2_mixer `pkg-config --libs glfw3` -ldl

GLAD = engine/glad/glad.c

RENDER = engine/render/render.c \
		 engine/render/render_init.c \
		 engine/render/render_utils.c

IO = engine/io/io.c

GLOBAL = engine/global/global.c

CONFIG = engine/config/config.c

INPUT = engine/input/input.c

TIME = engine/time/time.c

ENGINE = $(GLAD) \
		 $(RENDER) \
		 $(IO) \
		 $(GLOBAL) \
		 $(CONFIG) \
		 $(INPUT) \
		 $(TIME) \

SRCS = $(MAIN) \
	   $(ENGINE)

MAIN = main.c

CODE = $(MAIN) \
	   $(SRCS)

game: $(SRCS)
	$(CC) $(FLAGS) $(SRCS) $(LIBS) -o game

clean:
	rm config.ini

fclean: clean
	rm -rf game

re: clean game
