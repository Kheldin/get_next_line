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

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	t_list		*tmp;
	char		*res;
	t_list 		*head;
	int			ret;

	head = ft_lstnew("head");
	tmp = head;
	ret = 1;
	while (ret != 0 && !new_line_found(buf))
	{
    ret = read(fd, buf, BUFFER_SIZE);
    if (ret > 0)
        ft_lstadd_back(&head, ft_lstnew(buf));
	}
	while (tmp)
	{
		printf("%c\n", *(char *)tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

int	main(void)
{
	int	fd = open("test.txt", O_RDONLY);
	char *line;
	
	//printf("buffer size = %d\n", BUFFER_SIZE);
	get_next_line(fd);
	return (0);
}