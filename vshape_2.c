/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vshape_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 03:44:49 by apuddu            #+#    #+#             */
/*   Updated: 2025/02/10 03:48:39 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"
#include <stdlib.h>
#include <unistd.h>
#include <rt.h>

t_shape	vshape_back(t_vshape *vec)
{
	return (vec->arr[vec->size - 1]);
}

void	vshape_map_sub(t_vshape *vec, t_shape (*f)(t_shape))
{
	int	i;

	i = 0;
	while (i < vec->size)
	{
		vec->arr[i] = f(vec->arr[i]);
		i++;
	}
}
