/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vlu_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:13:52 by apuddu            #+#    #+#             */
/*   Updated: 2024/11/02 22:13:52 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"
#include <stdlib.h>
#include <unistd.h>

t_vlu	*vlu_init(int n, long unsigned int value)
{
	t_vlu	*res;

	res = malloc(sizeof(t_vlu));
	*res = (t_vlu){0, 0, 0};
	vlu_assign(res, n, value);
	return (res);
}

t_vlu	*vlu_uninit(int n)
{
	t_vlu	*res;

	res = malloc(sizeof(t_vlu));
	*res = (t_vlu){0, 0, 0};
	vlu_resize(res, n);
	return (res);
}

void	vlu_free(t_vlu *vec)
{
	free(vec->arr);
	free(vec);
}

t_vlu	*vlu_copy(t_vlu *vec)
{
	t_vlu	*res;

	res = safe_alloc(sizeof(t_vlu));
	res->size = vec->size;
	res->buf_size = vec->buf_size;
	res->arr = safe_alloc(sizeof(long unsigned int) * vec->buf_size);
	ft_memmove(res->arr, vec->arr, sizeof(long unsigned int) * vec->size);
	return (res);
}

void	vlu_map(t_vlu *vec, void (*f)(long unsigned int))
{
	int	i;

	i = 0;
	while (i < vec->size)
	{
		f(vec->arr[i]);
		i++;
	}
}
