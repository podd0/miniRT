/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:30:33 by apuddu            #+#    #+#             */
/*   Updated: 2024/06/26 18:16:51 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*double_str(char *str, size_t *csize)
{
	char	*res;

	res = malloc(*csize * 2 - 1);
	if (!res)
		return (NULL);
	ft_memmove(res, str, *csize);
	free(str);
	*csize = *csize * 2 - 1;
	return (res);
}

char	*buf_append(char *buf, t_buffer src, size_t *size, size_t *i)
{
	size_t	src_size;

	src_size = src.len;
	while (src_size + *i > *size)
		buf = double_str(buf, size);
	if (!buf)
		return (NULL);
	ft_memmove(buf + *i, src.str, src.len);
	*i += src_size;
	free(src.str);
	return (buf);
}

void	simple_checks(char format, t_flags *flags)
{
	if (format == ' ')
		flags->space = 1;
	else if (format == '-')
		flags->minus = 1;
	else if (format == '+')
		flags->plus = 1;
	else if (format == '#')
		flags->alt = 1;
	else if (ft_strchr(FLAGS_END, format))
		flags->flag = format;
}

t_buffer	handle_str(char *s)
{
	if (s)
		return ((t_buffer){ft_strdup(s), ft_strlen(s)});
	return ((t_buffer){ft_strdup("(null)"), 6});
}
