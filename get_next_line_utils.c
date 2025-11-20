/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacherch <kacherch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:13:34 by kacherch          #+#    #+#             */
/*   Updated: 2025/11/18 20:20:15 by kacherch         ###   ########.fr       */
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
	size_t	nb_bytes;

	if (nmemb != 0 && size > INT_MAX / nmemb)
		return (NULL);
	nb_bytes = nmemb * size;
	ptr = malloc(nb_bytes);
	if (!ptr)
		return (0);
	castedptr  = (unsigned char *)ptr;
	while (nb_bytes)
	{
		*castedptr = 0;
		castedptr++;
		nb_bytes--;
	}
	return (ptr);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = ft_calloc(1, sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = new;
}

char	*ft_strjoin(char const *s1, char const *s2)
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
