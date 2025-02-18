/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vch_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:13:53 by apuddu            #+#    #+#             */
/*   Updated: 2024/11/02 22:13:53 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"
#include <stdlib.h>
#include <unistd.h>

t_vch	*vch_init(int n, char value)
{
	t_vch	*res;

	res = malloc(sizeof(t_vch));
	*res = (t_vch){0, 0, 0};
	vch_assign(res, n, value);
	return (res);
}

t_vch	*vch_uninit(int n)
{
	t_vch	*res;

	res = malloc(sizeof(t_vch));
	*res = (t_vch){0, 0, 0};
	vch_resize(res, n);
	return (res);
}

void	vch_free(t_vch *vec)
{
	free(vec->arr);
	free(vec);
}

t_vch	*vch_copy(t_vch *vec)
{
	t_vch	*res;

	res = safe_alloc(sizeof(t_vch));
	res->size = vec->size;
	res->buf_size = vec->buf_size;
	res->arr = safe_alloc(sizeof(char) * vec->buf_size);
	ft_memmove(res->arr, vec->arr, sizeof(char) * vec->size);
	return (res);
}

void	vch_map(t_vch *vec, void (*f)(char))
{
	int	i;

	i = 0;
	while (i < vec->size)
	{
		f(vec->arr[i]);
		i++;
	}
}
