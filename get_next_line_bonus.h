/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacherch <kacherch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:48:27 by kacherch          #+#    #+#             */
/*   Updated: 2025/12/02 17:54:25 by kacherch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# define FDS_MAX 1024
# include <stdlib.h>

char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

typedef struct s_fds {
    int 	fd;
	char	*leftover;
	int		lenght;
} t_fds;

#endif