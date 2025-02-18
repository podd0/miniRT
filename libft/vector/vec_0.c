/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_0.c                                            :+:      :+:    :+:   */
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

void	vec_push_back(t_vector *vec, void *elem)
{
	int	new_buf_size;
	int	c_size;

	if (vec->size >= vec->buf_size)
	{
		c_size = vec->size;
		new_buf_size = vec->buf_size;
		if (new_buf_size < 16)
			new_buf_size = 16;
		vec_resize(vec, new_buf_size * 2);
		vec->size = c_size;
	}
	vec->arr[vec->size] = elem;
	vec->size++;
}

void	*vec_pop_back(t_vector *vec)
{
	if (vec->size == 0)
	{
		(void)!write(2, "Error: pop empty vector\n", 24);
		exit(1);
	}
	vec->size--;
	return (vec->arr[vec->size]);
}

void	vec_assign(t_vector *vec, int n, void *value)
{
	int	i;

	i = 0;
	vec->size = n;
	vec->buf_size = n;
	free(vec->arr);
	vec->arr = safe_alloc(n * sizeof(void *));
	while (i < n)
	{
		vec->arr[i] = value;
		i++;
	}
}

void	vec_resize(t_vector *vec, int n)
{
	t_vector	old;

	old = *vec;
	vec->size = n;
	vec->buf_size = n;
	vec->arr = safe_alloc(n * sizeof(void *));
	ft_memcpy(vec->arr, old.arr, old.size * sizeof(void *));
	free(old.arr);
}
