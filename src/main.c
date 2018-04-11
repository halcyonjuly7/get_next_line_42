//
// Created by Halcyon abrah Ramirez on 4/7/18.
//

#include <fcntl.h>
#include <stddef.h>
#include <libft.h>
#include <string.h>
#include <printf.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	if (argc > 1)
	{

		int fd = open(argv[1], O_RDONLY);
		char *line = ft_strnew(300);
		int resp;
		while ((resp = get_next_line(fd, &line)))
		{

			printf("%s\n", line);
			ft_strclr(line);
		}
//		ft_memdel((void *)&line);
	}
	return (0);
}
