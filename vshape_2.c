/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vshape_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:37:58 by amema             #+#    #+#             */
/*   Updated: 2025/02/25 15:37:59 by amema            ###   ########.fr       */
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
