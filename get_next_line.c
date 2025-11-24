/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacherch <kacherch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:13:42 by kacherch          #+#    #+#             */
/*   Updated: 2025/11/23 19:04:31 by kacherch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

char	*update_buffer(char *buf)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_calloc(ft_strlen(buf) * 2 + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (buf[i])
	{
		res[i] = buf[i];
		i++;
	}
	free(buf);
	return (res);
}

int	new_line_found(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

size_t	get_line_index(char *buf)
{
	size_t	i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	char		*tmpbuf;
	int			ret;

	ret = read(fd, buf, BUFFER_SIZE);
	tmpbuf = ft_strjoin("", buf);
	if (!tmpbuf)
		return (NULL);
	while (ret != 0)
	{
		if (new_line_found(tmpbuf))
			return (ft_substr(tmpbuf, 0, get_line_index(tmpbuf)));
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (NULL);
		tmpbuf = ft_strjoin(tmpbuf, buf);
	}
	return (tmpbuf);
}

int	main(void)
{
	int	fd = open("test.txt", O_RDONLY);
	char *line;

	//printf("buffer size = %d\n", BUFFER_SIZE);
	//printf("%s", get_next_line(fd));
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	return (0);
}