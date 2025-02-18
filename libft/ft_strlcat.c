/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:21:19 by apuddu            #+#    #+#             */
/*   Updated: 2024/03/23 19:36:43 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	char	*nulb;

	nulb = ft_memchr(dst, 0, size);
	if (nulb == NULL)
		return (size + ft_strlen(src));
	i = nulb - dst;
	return (i + ft_strlcpy(nulb, src, size - i));
}
