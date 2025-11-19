/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacherch <kacherch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:13:42 by kacherch          #+#    #+#             */
/*   Updated: 2025/11/18 20:19:24 by kacherch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			count;
	static char	buf[BUFFER_SIZE];

	count = 0;
	while (read(fd, buf, BUFFER_SIZE) > 0)
		write(1, buf, BUFFER_SIZE);
	return (NULL);
}

int	main(void)
{
	int	fd = open("test.txt", O_RDONLY);
	char *line;
	
	printf("buffer size = %d\n", BUFFER_SIZE);
	//get_next_line(fd);

	return (0);
}