/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vstr_1.c                                           :+:      :+:    :+:   */
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

t_vstr	*vstr_init(int n, char *value)
{
	t_vstr	*res;

	res = malloc(sizeof(t_vstr));
	*res = (t_vstr){0, 0, 0};
	vstr_assign(res, n, value);
	return (res);
}

t_vstr	*vstr_uninit(int n)
{
	t_vstr	*res;

	res = malloc(sizeof(t_vstr));
	*res = (t_vstr){0, 0, 0};
	vstr_resize(res, n);
	return (res);
}

void	vstr_free(t_vstr *vec)
{
	free(vec->arr);
	free(vec);
}

t_vstr	*vstr_copy(t_vstr *vec)
{
	t_vstr	*res;

	res = safe_alloc(sizeof(t_vstr));
	res->size = vec->size;
	res->buf_size = vec->buf_size;
	res->arr = safe_alloc(sizeof(char *) * vec->buf_size);
	ft_memmove(res->arr, vec->arr, sizeof(char *) * vec->size);
	return (res);
}

void	vstr_map(t_vstr *vec, void (*f)(char *))
{
	int	i;

	i = 0;
	while (i < vec->size)
	{
		f(vec->arr[i]);
		i++;
	}
}
