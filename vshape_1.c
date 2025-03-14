/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vshape_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:37:49 by amema             #+#    #+#             */
/*   Updated: 2025/02/25 15:37:50 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"
#include <stdlib.h>
#include <unistd.h>
#include <rt.h>

t_vshape	*vshape_init(int n, t_shape value)
{
	t_vshape	*res;

	res = malloc(sizeof(t_vshape));
	*res = (t_vshape){0, 0, 0};
	vshape_assign(res, n, value);
	return (res);
}

t_vshape	*vshape_uninit(int n)
{
	t_vshape	*res;

	res = malloc(sizeof(t_vshape));
	*res = (t_vshape){0, 0, 0};
	vshape_resize(res, n);
	return (res);
}

void	vshape_free(t_vshape *vec)
{
	free(vec->arr);
	free(vec);
}

t_vshape	*vshape_copy(t_vshape *vec)
{
	t_vshape	*res;

	res = safe_alloc(sizeof(t_vshape));
	res->size = vec->size;
	res->buf_size = vec->buf_size;
	res->arr = safe_alloc(sizeof(t_shape) * vec->buf_size);
	ft_memmove(res->arr, vec->arr, sizeof(t_shape) * vec->size);
	return (res);
}

void	vshape_map(t_vshape *vec, void (*f)(t_shape))
{
	int	i;

	i = 0;
	while (i < vec->size)
	{
		f(vec->arr[i]);
		i++;
	}
}
