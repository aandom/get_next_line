#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>



int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line;
	char	*line2;
	char	*line3;

	fd1 = open("aaaa.txt", O_RDONLY);
	fd2 = open("aaaa.txt", O_RDONLY);
	fd3 = open("aaaa.txt", O_RDONLY);
	int	n;

	n = 0;


	while (n < 1)
	{
		line = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);
		printf("%s", line);
		printf("%s", line2);
		printf("%s", line3);
		// if (line == NULL)
		// 	break ;
		free(line);
		free(line2);
		free(line3);
		n++;
	}
	// write(1, "this", 4);
	return (0);
}