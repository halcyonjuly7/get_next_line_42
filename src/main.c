//
// Created by Halcyon abrah Ramirez on 4/7/18.
//

#include <fcntl.h>
#include <stddef.h>
#include <libft.h>
#include <string.h>
#include <stdio.h>


#include "get_next_line.h"

int main(int argc, char **argv)
{
	if (argc > 1)
	{

		int fd = open(argv[1], O_RDONLY);
		char *line = NULL;
		int resp = 0;
		while ((resp = get_next_line(fd, &line)))
		{

			printf("%s\n", line);
			ft_strdel(&line);
		}
		close(fd);
		ft_strdel(&line);
//		ft_memdel((void *)&line);
	}
	return (0);
}
