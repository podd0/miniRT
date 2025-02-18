/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:20:43 by apuddu            #+#    #+#             */
/*   Updated: 2024/03/23 16:12:38 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*norminette_is_useless(int n, long pow, size_t dig, size_t i)
{
	char	*res;
	int		d;

	if (n == 0)
		return (ft_strdup("0"));
	while (n / pow)
	{
		dig++;
		pow *= 10;
	}
	pow /= 10;
	res = malloc(dig + 1 + (n < 0));
	if (n < 0)
		res[i++] = '-';
	while (pow > 0)
	{
		d = (n / pow) % 10;
		if (d < 0)
			d = -d;
		res[i++] = '0' + d;
		pow /= 10;
	}
	res[i] = 0;
	return (res);
}

char	*ft_itoa(int n)
{
	long	pow;
	int		dig;
	size_t	i;

	pow = 1;
	dig = 0;
	i = 0;
	return (norminette_is_useless(n, pow, dig, i));
}
