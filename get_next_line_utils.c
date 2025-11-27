/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacherch <kacherch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:13:34 by kacherch          #+#    #+#             */
/*   Updated: 2025/11/21 14:56:52 by kacherch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	unsigned char	*castedptr;
	size_t			nb_bytes;

	if (nmemb != 0 && size > INT_MAX / nmemb)
		return (NULL);
	nb_bytes = nmemb * size;
	ptr = malloc(nb_bytes);
	if (!ptr)
		return (0);
	castedptr = (unsigned char *)ptr;
	while (nb_bytes)
	{
		*castedptr = 0;
		castedptr++;
		nb_bytes--;
	}
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*res;
	unsigned int	i;
	unsigned int	j;
	size_t			total_len;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	res = ft_calloc(total_len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		res[j++] = s1[i++];
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	return (res);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (1)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return (i);
		if (s[i] == '\0')
			return (-1);
		i++;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_calloc(1, sizeof(char)));
	if (s_len - start < len)
		len = s_len - start;
	i = 0;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (i < len && s[start + i])
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
