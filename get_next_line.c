/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacherch <kacherch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:13:42 by kacherch          #+#    #+#             */
/*   Updated: 2025/12/04 12:21:42 by kacherch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char		*tmpbuf;
	char			*tmp;
	int				ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!tmpbuf)
		tmpbuf = ft_calloc(1, sizeof(char));
	if (!tmpbuf)
		return (NULL);
	while (1)
	{
		if (ft_strchr(tmpbuf, 10) != -1)
			return (extract_line(&tmpbuf));
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret <= 0)
			return (handle_read_end(&tmpbuf, ret));
		buf[ret] = '\0';
		tmp = ft_strjoin(tmpbuf, buf);
		free(tmpbuf);
		if (!tmp)
			return (tmpbuf = NULL);
		tmpbuf = tmp;
	}
}
