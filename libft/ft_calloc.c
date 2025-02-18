/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:05:09 by apuddu            #+#    #+#             */
/*   Updated: 2024/03/23 16:13:08 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	if (nmemb > (size_t)-1 / size)
		return (NULL);
	res = malloc(size * nmemb);
	if (res)
		ft_bzero(res, size * nmemb);
	return (res);
}
