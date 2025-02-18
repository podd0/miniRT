/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 03:47:58 by apuddu            #+#    #+#             */
/*   Updated: 2024/07/30 03:50:15 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*safe_alloc(int bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
	{
		ft_putendl_fd("Error: malloc fail", 2);
		exit(1);
	}
	return (ptr);
}
