/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_0.c                                             :+:      :+:    :+:   */
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

void	vi_push_back(t_vi *vec, int elem)
{
	int	new_buf_size;
	int	c_size;

	if (vec->size >= vec->buf_size)
	{
		c_size = vec->size;
		new_buf_size = vec->buf_size;
		if (new_buf_size < 16)
			new_buf_size = 16;
		vi_resize(vec, new_buf_size * 2);
		vec->size = c_size;
	}
	vec->arr[vec->size] = elem;
	vec->size++;
}

int	vi_pop_back(t_vi *vec)
{
	if (vec->size == 0)
	{
		(void)!write(2, "Error: pop empty vector\n", 24);
		exit(1);
	}
	vec->size--;
	return (vec->arr[vec->size]);
}

void	vi_assign(t_vi *vec, int n, int value)
{
	int	i;

	i = 0;
	vec->size = n;
	vec->buf_size = n;
	free(vec->arr);
	vec->arr = safe_alloc(n * sizeof(int));
	while (i < n)
	{
		vec->arr[i] = value;
		i++;
	}
}

void	vi_resize(t_vi *vec, int n)
{
	t_vi	old;

	old = *vec;
	vec->size = n;
	vec->buf_size = n;
	vec->arr = safe_alloc(n * sizeof(int));
	ft_memcpy(vec->arr, old.arr, old.size * sizeof(int));
	free(old.arr);
}
