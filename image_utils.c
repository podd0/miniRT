/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:16:59 by apuddu            #+#    #+#             */
/*   Updated: 2025/02/09 23:37:21 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

unsigned int	col_from_vec(t_vec3 v)
{
	return (((int)v.x << 16) | ((int)v.y << 8) | ((int)v.z));
}

void	pixel_put(t_img *img, int x, int y, t_vec3 color)
{
	char	*dst;

	if (x >= WIN_W || y >= WIN_H || x < 0 || y < 0 )
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = col_from_vec(color);
}

void	pixel_put_centered(t_img *img, int x, int y, t_vec3 color)
{
	x += WIN_W / 2;
	y += WIN_H / 2;
	pixel_put(img, x, y, color);
}
