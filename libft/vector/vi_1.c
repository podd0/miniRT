/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_1.c                                             :+:      :+:    :+:   */
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

t_vi	*vi_init(int n, int value)
{
	t_vi	*res;

	res = malloc(sizeof(t_vi));
	*res = (t_vi){0, 0, 0};
	vi_assign(res, n, value);
	return (res);
}

t_vi	*vi_uninit(int n)
{
	t_vi	*res;

	res = malloc(sizeof(t_vi));
	*res = (t_vi){0, 0, 0};
	vi_resize(res, n);
	return (res);
}

void	vi_free(t_vi *vec)
{
	free(vec->arr);
	free(vec);
}

t_vi	*vi_copy(t_vi *vec)
{
	t_vi	*res;

	res = safe_alloc(sizeof(t_vi));
	res->size = vec->size;
	res->buf_size = vec->buf_size;
	res->arr = safe_alloc(sizeof(int) * vec->buf_size);
	ft_memmove(res->arr, vec->arr, sizeof(int) * vec->size);
	return (res);
}

void	vi_map(t_vi *vec, void (*f)(int))
{
	int	i;

	i = 0;
	while (i < vec->size)
	{
		f(vec->arr[i]);
		i++;
	}
}
