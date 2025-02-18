/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vstr_0.c                                           :+:      :+:    :+:   */
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

void	vstr_push_back(t_vstr *vec, char *elem)
{
	int	new_buf_size;
	int	c_size;

	if (vec->size >= vec->buf_size)
	{
		c_size = vec->size;
		new_buf_size = vec->buf_size;
		if (new_buf_size < 16)
			new_buf_size = 16;
		vstr_resize(vec, new_buf_size * 2);
		vec->size = c_size;
	}
	vec->arr[vec->size] = elem;
	vec->size++;
}

char	*vstr_pop_back(t_vstr *vec)
{
	if (vec->size == 0)
	{
		(void)!write(2, "Error: pop empty vector\n", 24);
		exit(1);
	}
	vec->size--;
	return (vec->arr[vec->size]);
}

void	vstr_assign(t_vstr *vec, int n, char *value)
{
	int	i;

	i = 0;
	vec->size = n;
	vec->buf_size = n;
	free(vec->arr);
	vec->arr = safe_alloc(n * sizeof(char *));
	while (i < n)
	{
		vec->arr[i] = value;
		i++;
	}
}

void	vstr_resize(t_vstr *vec, int n)
{
	t_vstr	old;

	old = *vec;
	vec->size = n;
	vec->buf_size = n;
	vec->arr = safe_alloc(n * sizeof(char *));
	ft_memcpy(vec->arr, old.arr, old.size * sizeof(char *));
	free(old.arr);
}
