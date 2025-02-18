/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:22:15 by apuddu            #+#    #+#             */
/*   Updated: 2024/03/23 20:20:54 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*res;
	size_t	i;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = malloc(len);
	if (res == NULL)
		return (NULL);
	i = ft_strlcpy(res, s1, len);
	ft_strlcpy(res + i, s2, len - i + 1);
	return (res);
}
