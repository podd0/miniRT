/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vch_2.c                                            :+:      :+:    :+:   */
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

char	vch_back(t_vch *vec)
{
	return (vec->arr[vec->size - 1]);
}

void	vch_map_sub(t_vch *vec, char (*f)(char))
{
	int	i;

	i = 0;
	while (i < vec->size)
	{
		vec->arr[i] = f(vec->arr[i]);
		i++;
	}
}
