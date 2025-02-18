/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:10:44 by apuddu            #+#    #+#             */
/*   Updated: 2024/06/26 17:43:26 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdarg.h>
#include "printf_utils.h"

t_buffer	to_base(unsigned int n, const char *base_repr, int base)
{
	unsigned int	x;
	int				digits;
	char			*res;

	x = n;
	digits = 0;
	while (x)
	{
		x /= base;
		digits++;
	}
	if (digits == 0)
		digits = 1;
	res = (char *)malloc(digits + 1);
	if (!res)
		return ((t_buffer){(char *) NULL, 0});
	res[digits] = '\0';
	while (digits >= 1)
	{
		res[--digits] = base_repr[n % base];
		n /= base;
	}
	return ((t_buffer){res, ft_strlen(res)});
}

t_buffer	ptr_print(void *n, const char *base_repr, int base)
{
	unsigned long	x;
	int				digits;
	char			*res;

	if (!n)
		return ((t_buffer){ft_strdup("(nil)"), 5});
	x = (unsigned long)n;
	digits = 2;
	while (x)
	{
		x /= base;
		digits++;
	}
	x = (unsigned long)n;
	res = (char *)ft_calloc(digits + 1, 1);
	if (!res)
		return ((t_buffer){NULL, 0});
	res[0] = '0';
	res[1] = 'x';
	while (digits >= 3)
	{
		res[--digits] = base_repr[x % base];
		x /= base;
	}
	return ((t_buffer){res, ft_strlen(res)});
}

t_buffer	to_buffer(char *s)
{
	return ((t_buffer){s, ft_strlen(s)});
}

t_buffer	to_string(char flag, va_list ls)
{
	char	*res;

	if (flag == 'c')
	{
		res = ft_calloc(2, 1);
		res[0] = va_arg(ls, int);
		return ((t_buffer){res, 1});
	}
	if (flag == 's')
		return (handle_str(va_arg(ls, char *)));
	if (flag == 'd' || flag == 'i')
		return (to_buffer(ft_itoa(va_arg(ls, int))));
	if (flag == 'x')
		return (to_base(va_arg(ls, unsigned), "0123456789abcdef", 16));
	if (flag == 'X')
		return (to_base(va_arg(ls, unsigned), "0123456789ABCDEF", 16));
	if (flag == 'u')
		return (to_base(va_arg(ls, int), "0123456789", 10));
	if (flag == 'p')
		return (ptr_print(va_arg(ls, void *), "0123456789abcdef", 16));
	if (flag == '%')
		return (to_buffer(ft_strdup("%")));
	return ((t_buffer){(char *) NULL, 0});
}
