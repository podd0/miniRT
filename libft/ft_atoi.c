/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:04:52 by apuddu            #+#    #+#             */
/*   Updated: 2024/03/23 19:55:36 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_isspace(int c)
{
	return (c == ' ' || (9 <= c && c <= 13));
}

int	ft_atoi(const char *s)
{
	long	x;
	int		i;
	int		neg;

	x = 0;
	i = 0;
	neg = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-')
	{
		i++;
		neg = 1;
	}
	else if (s[i] == '+')
		i++;
	while (ft_isdigit(s[i]))
	{
		x *= 10;
		x += s[i] - '0';
		i++;
	}
	if (neg)
		x = -x;
	return ((int)x);
}
