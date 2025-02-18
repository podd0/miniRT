/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:41:28 by apuddu            #+#    #+#             */
/*   Updated: 2024/03/23 20:36:36 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static void	norminette_is_useless(int n, int fd, long pow, size_t dig)
{
	int	d;

	while (n / pow)
	{
		dig++;
		pow *= 10;
	}
	pow /= 10;
	while (pow > 0)
	{
		d = (n / pow) % 10;
		if (d < 0)
			d = -d;
		ft_putchar_fd('0' + d, fd);
		pow /= 10;
	}
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	long	pow;
	int		dig;

	pow = 1;
	dig = 0;
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	return (norminette_is_useless(n, fd, pow, dig));
}
