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

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_lstaddback(t_list **node, void *content)
{
	while ((*node)->next)
		*node = (*node)->next;
	(*node)->next = ft_lstnew(content);
}
