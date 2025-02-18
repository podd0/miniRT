/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 00:58:19 by apuddu            #+#    #+#             */
/*   Updated: 2025/02/05 19:48:10 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*consume_head(char *left, size_t len)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	while (i < len)
	{
		ret[i] = left[i];
		i++;
	}
	while (left[i])
	{
		left[i - len] = left[i];
		i++;
	}
	left[i - len] = '\0';
	return (ret);
}

char	*append_cum(char *cum, char *left, size_t end_cum, ssize_t b_read)
{
	char	t;
	ssize_t	i;

	i = b_read + 1;
	t = left[b_read + 1];
	left[b_read + 1] = 0;
	ft_strcpy(cum, left, end_cum);
	left[b_read + 1] = t;
	while (left[i])
	{
		left[i - b_read - 1] = left[i];
		i++;
	}
	left[i - b_read - 1] = '\0';
	return (cum);
}

char	*get_line(int fd, char **left, size_t i, size_t size)
{
	char	*cum;
	ssize_t	b_read;

	cum = malloc(size);
	i = ft_strcpy(cum, *left, i);
	b_read = read(fd, *left, BUFFER_SIZE);
	while (b_read > 0)
	{
		(*left)[b_read] = '\0';
		if (b_read + i + 2 > size)
			cum = double_cum(cum, &size);
		b_read = has_end(*left);
		if (b_read != -1)
			return (append_cum(cum, *left, i, b_read));
		i = ft_strcpy(cum, *left, i);
		b_read = read(fd, *left, BUFFER_SIZE);
	}
	free(*left);
	*left = 0;
	if (cum[0])
		return (cum);
	free(cum);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*left[4096];
	ssize_t		i;

	if (!left[fd])
	{
		left[fd] = malloc(BUFFER_SIZE + 1);
		left[fd][0] = '\0';
	}
	i = has_end(left[fd]);
	if (i != -1)
	{
		return (consume_head(left[fd], i + 1));
	}
	return (get_line(fd, &left[fd], 0, BUFFER_SIZE * 2 + 1));
}
