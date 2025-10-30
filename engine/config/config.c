#include "../global.h"
#include "../io.h"
#include "../util.h"

static const char *CONFIG_DEFAULT =
		"[controls]\n"
		"left = A\n"
		"right = D\n"
		"up = W\n"
		"down = S\n"
		"escape = Escape\n"
		"\n";

static char	tmp_buffer[40] = {0};

static char	*config_get_value(const char *config_buffer, const char *value)
{
	char	*line;
	char	*end;
	char	*tmp_ptr;
	char	*curr;
	size_t	len;

	line = strstr(config_buffer, value);
	if (line == NULL)
	{
		ERROR_EXIT("Could not find config value: %s, "
					"Try deleting config.ini and restarting\n", value);
	}

	len = strlen(line);
	end = line + len;

	curr = line;
	tmp_ptr = &tmp_buffer[0];
	// Move pointer to '='
	while (*curr != '=' && curr != end)
		curr++;
	// Consume '='
	curr++;
	// Consume any spaces
	while (*curr == ' ')
		curr++;
	// Get characters until end of line
	while (*curr != '\n' && *curr != 0 && curr != end)
		*tmp_ptr++ = *curr++;
	*(tmp_ptr + 1) = '\0';

	return (tmp_buffer);
}

static void	load_controls(const char *config_buffer)
{
	config_key_bind(INPUT_KEY_LEFT, config_get_value(config_buffer, "left")); 
	config_key_bind(INPUT_KEY_RIGHT, config_get_value(config_buffer, "right"));
	config_key_bind(INPUT_KEY_UP, config_get_value(config_buffer, "up"));
	config_key_bind(INPUT_KEY_DOWN, config_get_value(config_buffer, "down"));
	config_key_bind(INPUT_KEY_ESCAPE, config_get_value(config_buffer, "escape"));
}

static int	config_load(void)
{
	File	file_config;

	config_controller_bind(INPUT_DPAD_LEFT, "gamepad_dpleft");

	file_config = io_file_read("./config.ini");
	if (!file_config.is_valid)
			return (1);

	load_controls(file_config.data);

	free(file_config.data);

	return (0);
}

void	config_init(void)
{
	int	game_pad_load;

	game_pad_load = SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");

	if (config_load() == 0)
		return ;

	io_file_write((void *) CONFIG_DEFAULT, strlen(CONFIG_DEFAULT), "./config.ini");

	if (config_load() != 0 || game_pad_load == 0)
		ERROR_EXIT("Could not create or load config files\n");
}

void	config_controller_bind(Input_Pad key, const char *button_name)
{
	SDL_GameControllerButton	button_code;
	char						*button_string;
	//SDL_GameControllerAxis		axis;
	//int							axis_dir;

	button_code = SDL_CONTROLLER_BUTTON_INVALID;
	//axis = SDL_CONTROLLER_AXIS_INVALID;
	//axis_dir = 0;

	if (!button_name || !*button_name)
	{
		ERROR_RETURN(, "Empty button code: %s\n", button_name);
	}

	if (strncmp(button_name, "gamepad_", 8) == 0)
	{
		button_string = (char *) button_name + 8;
		button_code = SDL_GameControllerGetButtonFromString(button_string);

		if (button_code == SDL_CONTROLLER_BUTTON_INVALID)
			ERROR_RETURN(, "Invalid button code: %s\n", "dpleft");

		global.config.padbinds[key] = button_code;
	}
	else
		ERROR_RETURN(, "Invalid pad_input name: %s\n", button_name);
}

void	config_key_bind(Input_Key key, const char *key_name)
{
	SDL_Scancode	scan_code;

	scan_code = SDL_GetScancodeFromName(key_name);
	if (scan_code == SDL_SCANCODE_UNKNOWN)
		ERROR_RETURN(, "Invalid scan code when binding key: %s\n", key_name);

	global.config.keybinds[key] = scan_code;
}
