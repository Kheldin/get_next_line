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

	while (buf[i])
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
void	buf_to_list(t_list *head, char *buf)
{
	size_t	i;

	i = 0;
	while (buf[i])
	{
		ft_lstaddback(head, &buf[i]);
		i++;
	}
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	t_list		*tmp;
	char		*res;
	t_list 		*head;

	head = ft_lstnew("head");
	tmp = head;
	read(fd, buf, BUFFER_SIZE - 1);
	buf_to_list(tmp, buf);
	buf[BUFFER_SIZE] = '\0';
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
	
	printf("buffer size = %d\n", BUFFER_SIZE);
	get_next_line(fd);
	return (0);
}