/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:04:17 by apuddu            #+#    #+#             */
/*   Updated: 2024/11/02 22:15:03 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf_utils.h"
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

void	build_flags(const char **format, t_flags *flags)
{
	while (**format && flags->flag == 0)
	{
		if (**format == '0')
			flags->zero = 1;
		else if (ft_isdigit(**format))
		{
			flags->width = ft_atoi(*format);
			while (ft_isdigit(*((*format) + 1)))
				(*format)++;
		}
		else if (**format == '.')
		{
			flags->precision = ft_atoi(++(*format));
			while (ft_isdigit(*((*format) + 1)))
				(*format)++;
		}
		else
			simple_checks(**format, flags);
		(*format)++;
	}
}

static t_buffer	handle(const char **format, va_list ptr)
{
	t_flags	flags;

	flags = (t_flags){0, 0, 0, 0, 0, 0, 0, 0};
	(*format)++;
	build_flags(format, &flags);
	return (to_string(flags.flag, ptr));
}

static t_buffer	ft_printf_core_core(const char **format, size_t *size,
		va_list ptr, char *res)
{
	size_t	i;

	i = 0;
	while (**format)
	{
		if (i >= *size - 2)
		{
			res = double_str(res, size);
		}
		if (**format == '%')
		{
			res = buf_append(res, handle(format, ptr), size, &i);
		}
		else
		{
			res[i] = **format;
			(*format)++;
			i++;
		}
	}
	res[i] = '\0';
	return ((t_buffer){res, i});
}

static t_buffer	ft_printf_core(const char **format, size_t *size, va_list ptr)
{
	char	*res;

	res = malloc(*size);
	if (!res)
		exit(1);
	return (ft_printf_core_core(format, size, ptr, res));
}

int	ft_printf(const char *format, ...)
{
	va_list		ptr;
	size_t		size;
	t_buffer	res;

	va_start(ptr, format);
	size = ft_strlen(format) + 10;
	res = ft_printf_core(&format, &size, ptr);
	if (write(1, res.str, res.len) < 0)
	{
		free(res.str);
		return (-1);
	}
	free(res.str);
	return (res.len);
}
