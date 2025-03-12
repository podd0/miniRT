/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:18:45 by amema             #+#    #+#             */
/*   Updated: 2025/03/12 11:55:55 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	aces_tone_mapping(t_vec3 color)
{
	t_vec3	numerator;
	t_vec3	denominator;
	t_vec3	res;

	numerator = pairwise_mul(color, add(scale(ACES_A, color), cvec(ACES_B)));
	denominator = add(pairwise_mul(color, add(scale(ACES_C, color),
					cvec(ACES_D))), cvec(ACES_E));
	res = scale(255, pairwise_div(numerator, denominator));
	return (clamp(res));
}

t_vec3	tone_map(t_vec3 v)
{
	v.x /= v.x + 1.0;
	v.y /= v.y + 1.0;
	v.z /= v.z + 1.0;
	v = scale(255, v);
	return (v);
}

/*
update_image:
Using: ctx->win_w and ctx->win_h instead of macros.
Calculate the index as y * ctx->win_w + x to access img_vec.
Use calc_direction with dynamic parameters.
*/
void	update_image(t_ctx *ctx)
{
	int		x;
	int		y;
	int		index;
	t_vec3	direction;
	t_vec3	color;

	index = 0;
	while (index < ctx->win_w * ctx->win_h)
	{
		x = index % ctx->win_w;
		y = index / ctx->win_w;
		direction = calc_direction((t_screen){x, y, ctx->win_w, ctx->win_h},
				ctx->scene->fov, ctx->scene->camera);
		if (ctx->control.path_tracing)
			color = shade_path(direction, ctx->scene->camera.o,
					ctx->scene, N_BOUNCES);
		else
			color = shade_ray(direction, ctx->scene->camera.o,
					ctx->scene);
		ctx->img_vec[index] = add(ctx->img_vec[index], color);
		index++;
	}
}

/*
show_image:
Iterate using ctx->win_w and ctx->win_h and calculate index
as y * ctx->win_w + x.
Then apply tone mapping and call pixel_put.
*/

void	show_image(t_ctx *ctx, int rounds)
{
	int		x;
	int		y;
	int		index;
	t_vec3	color;

	x = 0;
	while (x < ctx->win_w)
	{
		y = 0;
		while (y < ctx->win_h)
		{
			index = y * ctx->win_w + x;
			color = scale(1.0 / rounds, ctx->img_vec[index]);
			color = aces_tone_mapping(color);
			pixel_put(ctx->img, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, ctx->img->img, 0, 0);
}

/*
update_show:
Increase rounds, call update_image and then show_image.
*/

void	update_show(t_ctx *ctx)
{
	ctx->rounds += 1;
	update_image(ctx);
	show_image(ctx, ctx->rounds);
}
