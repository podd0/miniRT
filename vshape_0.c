/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vshape_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 03:44:49 by apuddu            #+#    #+#             */
/*   Updated: 2025/02/10 03:48:33 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"
#include <stdlib.h>
#include <unistd.h>
#include <rt.h>

void	vshape_push_back(t_vshape *vec, t_shape elem)
{
	int	new_buf_size;
	int	c_size;

	if (vec->size >= vec->buf_size)
	{
		c_size = vec->size;
		new_buf_size = vec->buf_size;
		if (new_buf_size < 16)
			new_buf_size = 16;
		vshape_resize(vec, new_buf_size * 2);
		vec->size = c_size;
	}
	vec->arr[vec->size] = elem;
	vec->size++;
}

t_shape	vshape_pop_back(t_vshape *vec)
{
	if (vec->size == 0)
	{
		(void)!write(2, "Error: pop empty vector\n", 24);
		exit(1);
	}
	vec->size--;
	return (vec->arr[vec->size]);
}

void	vshape_assign(t_vshape *vec, int n, t_shape value)
{
	int	i;

	i = 0;
	vec->size = n;
	vec->buf_size = n;
	free(vec->arr);
	vec->arr = safe_alloc(n * sizeof(t_shape));
	while (i < n)
	{
		vec->arr[i] = value;
		i++;
	}
}

void	vshape_resize(t_vshape *vec, int n)
{
	t_vshape	old;

	old = *vec;
	vec->size = n;
	vec->buf_size = n;
	vec->arr = safe_alloc(n * sizeof(t_shape));
	ft_memcpy(vec->arr, old.arr, old.size * sizeof(t_shape));
	free(old.arr);
}
