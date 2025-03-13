/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:28:12 by amema             #+#    #+#             */
/*   Updated: 2025/03/13 19:41:51 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	get_sign(char **str, int *err)
{
	if (!*str)
	{
		*err = 1;
		return (0);
	}
	if (**str == '-')
	{
		(*str)++;
		return (-1);
	}
	if (**str == '+')
		(*str)++;
	return (1);
}

float	get_integer_part(char **str, int *err)
{
	float	res;

	if (*err)
		return (0.0);
	res = 0.0;
	while (**str && **str != '.')
	{
		if (!ft_isdigit(**str))
		{
			*err = 1;
			return (0.0);
		}
		res *= 10;
		res += (**str - '0');
		(*str)++;
	}
	return (res);
}

float	parse_float(char *str, int *err)
{
	float	integer;
	float	frac;
	int		sign;

	if (!str)
		*err = 1;
	if (*err)
		return (0.0);
	sign = get_sign(&str, err);
	integer = get_integer_part(&str, err);
	if (*str == '\0' || *err)
		return (integer * sign);
	str++;
	frac = get_integer_part(&str, err);
	if (*str != '\0')
		*err = 1;
	if (*err)
		return (0.0);
	while (frac >= 1)
		frac /= 10.0;
	return (sign * (integer + frac));
}

int	arg_len(char **arr)
{
	int	l;

	l = 0;
	if (arr == NULL)
		return (-1);
	while (arr[l] != NULL)
	{
		l++;
	}
	return (l);
}

t_vec3	parse_vec(char *s, int *fail)
{
	char	**splitted;
	t_vec3	res;

	if (!s)
	{
		*fail = 1;
		return ((t_vec3){0, 0, 0});
	}
	splitted = ft_split(s, ',');
	*fail = *fail || arg_len(splitted) != 3 || count_char(s, ',') != 2;
	if (*fail)
	{
		ft_split_free(splitted);
		return ((t_vec3){0, 0, 0});
	}
	res.x = parse_float(splitted[0], fail);
	res.y = parse_float(splitted[1], fail);
	res.z = parse_float(splitted[2], fail);
	ft_split_free(splitted);
	return (res);
}
