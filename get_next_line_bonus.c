/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacherch <kacherch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:52:56 by kacherch          #+#    #+#             */
/*   Updated: 2025/12/02 20:47:30 by kacherch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	get_line_index(char *buf)
{
	size_t	i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	return (i);
}

static char	*create_remaining_buffer(char *buf, size_t line_len)
{
	char	*res;
	size_t	i;

	if (ft_strchr(buf, 10) != -1)
		return (ft_substr(buf, line_len, ft_strlen(buf) - line_len));
	res = ft_calloc(ft_strlen(buf) + BUFFER_SIZE + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (buf[i])
	{
		res[i] = buf[i];
		i++;
	}
	return (res);
}

static char	*extract_line(char **buf)
{
	char	*line;
	char	*new_buf;

	line = ft_substr(*buf, 0, ft_strchr(*buf, 10) + 1);
	if (!line)
	{
		free(*buf);
		*buf = NULL;
		return (NULL);
	}
	new_buf = create_remaining_buffer(*buf, get_line_index(*buf));
	free(*buf);
	if (!new_buf)
	{
		free(line);
		*buf = NULL;
		return (NULL);
	}
	*buf = new_buf;
	return (line);
}

static char	*handle_read_end(char **tmpbuf, int ret)
{
	char	*line;

	if (ret < 0 || !(*tmpbuf) || (*tmpbuf)[0] == '\0')
	{
		free(*tmpbuf);
		*tmpbuf = NULL;
		return (NULL);
	}
	line = *tmpbuf;
	*tmpbuf = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	char			buf[BUFFER_SIZE + 1];
	static char		*tmpbuf[FDS_MAX];
	char			*tmp;
	int				ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!tmpbuf[fd])
		tmpbuf[fd] = ft_calloc(1, sizeof(char));
	if (!tmpbuf[fd])
		return (NULL);
	while (1)
	{
		if (ft_strchr(tmpbuf[fd], 10) != -1)
			return (extract_line(&tmpbuf[fd]));
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret <= 0)
			return (handle_read_end(&tmpbuf[fd], ret));
		buf[ret] = '\0';
		tmp = ft_strjoin(tmpbuf[fd], buf);
		free(tmpbuf[fd]);
		if (!tmp)
			return (tmpbuf[fd] = NULL);
		tmpbuf[fd] = tmp;
	}
}

/* #include <fcntl.h>
#include <unistd.h>
int main (void)
{
    int fd = open("test.txt", O_RDONLY);
    int fd2 = open("test2.txt", O_RDONLY);
    
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd2));
    printf("%s", get_next_line(fd2));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd2));
    return (0);
} */