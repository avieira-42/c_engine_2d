#include "global/global.h"
#include "io/io.h"
#include "util.h"

void	config_init(void)
{
	if (config_load() == 0)
		return ;

	io_file_write((void *) CONFIG_DEFAULT, srlen(CONFIG_DEFAULT), "./config.init")
}
