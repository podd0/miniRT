/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:25:12 by apuddu            #+#    #+#             */
/*   Updated: 2024/03/24 19:46:59 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	char	*sub_end;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	sub_end = (char *)ft_memchr(s + start, 0, len);
	if (sub_end)
		len = sub_end - (s + start);
	res = malloc(len + 1);
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, s + start, len);
	res[len] = 0;
	return (res);
}
