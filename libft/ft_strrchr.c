/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:04:00 by apuddu            #+#    #+#             */
/*   Updated: 2024/03/23 18:46:18 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*ret;

	if (!s)
		return (NULL);
	ret = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			ret = (char *)&s[i];
		i++;
	}
	if (s[i] == c)
		ret = (char *)&s[i];
	return (ret);
}
