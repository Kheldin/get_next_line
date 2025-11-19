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

void	ft_lstaddback(t_list *node, void *content)
{
	t_list	*tmp;

	tmp = node;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_lstnew(content);
}
