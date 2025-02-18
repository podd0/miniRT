/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:13:53 by apuddu            #+#    #+#             */
/*   Updated: 2025/02/06 00:35:47 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"
#include <stdlib.h>
#include <unistd.h>

t_vector	*vec_init(int n, void *value)
{
	t_vector	*res;

	res = malloc(sizeof(t_vector));
	*res = (t_vector){0, 0, 0};
	vec_assign(res, n, value);
	return (res);
}

t_vector	*vec_uninit(int n)
{
	t_vector	*res;

	res = malloc(sizeof(t_vector));
	*res = (t_vector){0, 0, 0};
	vec_resize(res, n);
	return (res);
}

void	vec_free(t_vector *vec)
{
	free(vec->arr);
	free(vec);
}

t_vector	*vec_copy(t_vector *vec)
{
	t_vector	*res;

	res = safe_alloc(sizeof(t_vector));
	res->size = vec->size;
	res->buf_size = vec->buf_size;
	res->arr = safe_alloc(sizeof(void *) * vec->buf_size);
	ft_memmove(res->arr, vec->arr, sizeof(void *) * vec->size);
	return (res);
}

void	vec_map(t_vector *vec, void (*f)(void *))
{
	int	i;

	i = 0;
	while (i < vec->size)
	{
		f(vec->arr[i]);
		i++;
	}
}
