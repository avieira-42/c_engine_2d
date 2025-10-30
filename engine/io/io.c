#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../util.h"
#include "../io.h"

// 20 Mib, can probably change this to a higher value without issue
// Check your target platform.
#define IO_READ_CHUNK_SIZE 2097152 // exactly 2MiB (memibytes) a good amount to read shaders
#define IO_READ_ERROR_GENERAL "Error reading file: %s. errno: %d\n"
#define IO_READ_ERROR_MEMORY "Not enough free memory to read file: %s\n"

// Adapted from https://stackoverflow.com/a/44894946 (not the chosen answer) by Nominal Animal
File	io_file_read(const char *path)
{
	FILE	*fp;
	File	file;
	char	*data;
	char	*tmp;
	size_t	used;
	size_t	size;
	size_t	n;
	
	file.is_valid = false;

	// open file
	fp = fopen(path, "rb");
	if (!fp || ferror(fp))
	{
		ERROR_RETURN(file, IO_READ_ERROR_GENERAL, path, errno);
	}

	data = NULL;
	used = 0; // bytes_read
	size = 0; // next size to allocate

	while (true)
	{
		// if size isnt enough to hold previous bytes read + chunk
		if (used + IO_READ_CHUNK_SIZE + 1 > size)
		{
			// size is previous bytes read + chunk
			size = used + IO_READ_CHUNK_SIZE + 1;

			// return error in case of overflow
			if (size <= used) 
			{
				free(data);
				ERROR_RETURN(file,  "Input file too large: %s\n", path);
			}

			// reallocate the size of file read data
			tmp = realloc(data, size);
			if (!tmp)
			{
				free(data);
				ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
			}
			data = tmp;
		}

		// read from file
		n = fread(data + used, 1, IO_READ_CHUNK_SIZE, fp);
		if (n == 0)
			break;

		used += n;
	}

	// if no file pointer, close process
	if (!fp || ferror(fp))
	{
		free(data);
		ERROR_RETURN(file, IO_READ_ERROR_GENERAL, path, errno);
	}

	// reallocate data
	tmp = realloc(data, used + 1);
	if (!tmp)
	{
		free(data);
		ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
	}
	data = tmp;
	data[used] = 0;

	file.data = data;
	file.len = used;
	file.is_valid = true;

	return (file);
}

int	io_file_write(void *buffer, size_t size, const char *path)
{
	FILE	*fp;
	size_t	chunks_written;

	fp = fopen(path, "wb");
	if (!fp || ferror(fp))
	{
		ERROR_RETURN(1, "Cannot write file: %s.\n", path);
	}

	chunks_written = fwrite(buffer, size, 1, fp);
	fclose(fp);
	if(chunks_written != 1)
	{
		ERROR_RETURN(1, "Write error. "
						"Expected 1 chunk, got %zu.\n", chunks_written);
	}

	return (0);
}
