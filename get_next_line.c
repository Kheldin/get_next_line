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

void	update_buffer(char *buf)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_calloc(ft_strlen(buf) + BUFFER_SIZE + 1, sizeof(char));
	if (!res)
		return ;
	if (ft_strchr(buf, 10) != -1)
		res = ft_substr(buf, get_line_index(buf), ft_strlen(buf) - get_line_index(buf));
	else
	{
		while (buf[i])
		{
			res[i] = buf[i];
			i++;
		}
	}
	free(buf);
}

char	*get_next_line(int fd)
{
	char			buf[BUFFER_SIZE];
	static char		*tmpbuf;
	int				ret;

	ret = read(fd, buf, BUFFER_SIZE);
	tmpbuf = NULL;
	tmpbuf = ft_strjoin("", buf);
	if (!tmpbuf)
		return (NULL);
	while (ret != 0)
	{
		if (ft_strchr(tmpbuf, 10))
		{
			update_buffer(tmpbuf);
			return (ft_substr(tmpbuf, 0, ft_strchr(tmpbuf, 10)));
		}
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (NULL);
		free(tmpbuf);
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