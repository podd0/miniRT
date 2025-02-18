/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:54:44 by apuddu            #+#    #+#             */
/*   Updated: 2024/03/23 16:13:02 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	l;
	size_t	r;

	l = 0;
	r = ft_strlen(s1);
	while (r && ft_strchr(set, s1[r - 1]))
	{
		r--;
	}
	if (r == 0)
	{
		return (ft_strdup(""));
	}
	while (ft_strchr(set, s1[l]))
	{
		l++;
	}
	return (ft_substr(s1, l, r - l));
}
