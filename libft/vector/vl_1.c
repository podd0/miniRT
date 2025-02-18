/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vl_1.c                                             :+:      :+:    :+:   */
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

t_vl	*vl_init(int n, long value)
{
	t_vl	*res;

	res = malloc(sizeof(t_vl));
	*res = (t_vl){0, 0, 0};
	vl_assign(res, n, value);
	return (res);
}

t_vl	*vl_uninit(int n)
{
	t_vl	*res;

	res = malloc(sizeof(t_vl));
	*res = (t_vl){0, 0, 0};
	vl_resize(res, n);
	return (res);
}

void	vl_free(t_vl *vec)
{
	free(vec->arr);
	free(vec);
}

t_vl	*vl_copy(t_vl *vec)
{
	t_vl	*res;

	res = safe_alloc(sizeof(t_vl));
	res->size = vec->size;
	res->buf_size = vec->buf_size;
	res->arr = safe_alloc(sizeof(long) * vec->buf_size);
	ft_memmove(res->arr, vec->arr, sizeof(long) * vec->size);
	return (res);
}

void	vl_map(t_vl *vec, void (*f)(long))
{
	int	i;

	i = 0;
	while (i < vec->size)
	{
		f(vec->arr[i]);
		i++;
	}
}
