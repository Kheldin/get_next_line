/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacherch <kacherch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:13:42 by kacherch          #+#    #+#             */
/*   Updated: 2025/11/28 12:08:05 by kacherch         ###   ########.fr       */
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

char	*update_buffer(char *buf)
{
	char	*res;
	int		i;

	i = 0;
	if (ft_strchr(buf, 10) != -1)
	{
		res = ft_substr(buf, get_line_index(buf),
				ft_strlen(buf) - get_line_index(buf));
		if (!res)
		{
			free(buf);
			return (NULL);
		}
	}
	else
	{
		res = ft_calloc(ft_strlen(buf) + BUFFER_SIZE + 1, sizeof(char));
		if (!res)
		{
			free(buf);
			return (NULL);
		}
		while (buf[i])
		{
			res[i] = buf[i];
			i++;
		}
	}
	free(buf);
	return (res);
}

char	*get_next_line(int fd)
{
	char			buf[BUFFER_SIZE + 1];
	static char		*tmpbuf;
	char			*tmp;
	int				ret;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!tmpbuf)
		tmpbuf = ft_calloc(1, sizeof(char));
	if (!tmpbuf)
		return (NULL);
	while (1)
	{
		if (ft_strchr(tmpbuf, 10) != -1)
		{
			line = ft_substr(tmpbuf, 0, ft_strchr(tmpbuf, 10) + 1);
			if (!line)
			{
				free(tmpbuf);
				tmpbuf = NULL;
				return (NULL);
			}
			tmpbuf = update_buffer(tmpbuf);
			if (!tmpbuf)
			{
				free(line);
				return (NULL);
			}
			return (line);
		}
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free(tmpbuf);
			tmpbuf = NULL;
			return (NULL);
		}
		if (ret == 0)
		{
			if (tmpbuf && tmpbuf[0] != '\0')
			{
				line = tmpbuf;
				tmpbuf = NULL;
				return (line);
			}
			free(tmpbuf);
			tmpbuf = NULL;
			return (NULL);
		}
		buf[ret] = '\0';
		tmp = ft_strjoin(tmpbuf, buf);
		if (!tmp)
		{
			free(tmpbuf);
			tmpbuf = NULL;
			return (NULL);
		}
		free(tmpbuf);
		tmpbuf = tmp;
	}
}

/* int	main(void)
{
	int	fd = open("test.txt", O_RDONLY);
	char *line;

	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);
	return (0);
} */