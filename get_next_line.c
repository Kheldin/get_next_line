/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacherch <kacherch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:13:42 by kacherch          #+#    #+#             */
/*   Updated: 2025/11/21 11:58:16 by kacherch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

int	new_line_found(char *buf)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_line(char *buf)
{
	int		i;
	int		count;
	char	*res;

	i = 0;
	count = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	res = ft_calloc(i + 1, sizeof(char));
	if (!res)
		return (NULL);
	count = i;
	i = 0;
	while (i < count)
	{	
		res[i] = buf[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	char		*tmpbuf;
	int			count;

	count = 1;
	tmpbuf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (1)
	{
		read(fd, buf, BUFFER_SIZE);
		if (new_line_found(buf))
			return (get_line(buf));
		free(tmpbuf);
		tmpbuf = ft_calloc((BUFFER_SIZE * count) + 1, sizeof(char));
		if (!tmpbuf)
			return (NULL);
		ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	}
	return (NULL);
}

int	main(void)
{
	int	fd = open("test.txt", O_RDONLY);
	char *line;
	
	//printf("buffer size = %d\n", BUFFER_SIZE);
	printf("%s", get_next_line(fd));
	return (0);
}