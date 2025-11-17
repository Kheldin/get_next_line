#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	int		count;
	char	res[BUFFER_SIZE];

	count = 0;
	while (read(fd, res, BUFFER_SIZE) > 0)
		write(1, res, BUFFER_SIZE);
	return (NULL);
}

int main(void)
{
	int	fd = open("test.txt", O_RDONLY);
	char *line;

	get_next_line(fd);
	return (0);
}