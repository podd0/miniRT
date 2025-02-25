/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:23:36 by amema             #+#    #+#             */
/*   Updated: 2025/02/25 16:01:59 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <stdio.h>

t_vec3	calc_direction(int x, int y, float fov, t_frame camera, int win_w, int win_h)
{
	float	unit_rot;
	t_vec3	v;
	float	dx;
	float	dy;

	dx = drand48() - 0.5;
	dy = drand48() - 0.5;
	x -= win_w / 2;
	y -= win_h / 2;
	unit_rot = fov / max(win_h, win_w);
	v = rotx((dy + y) * unit_rot).z;
	v = to_world(v, roty((dx + x) * unit_rot));
	return (to_world(v, camera));
}

t_vec3	ray_at(float t, t_vec3 direction, t_vec3 origin)
{
	return (add(scale(t, direction), origin));
}

t_shape	*intersect_scene(t_vec3 *p, t_vec3 direction, t_scene *scene, t_vec3 o)
{
	int		i;
	t_shape	*best;
	float	t;
	t_shape	*shape;
	float	mn;

	mn = INFINITY;
	best = NULL;
	i = 0;
	while (i < scene->objects->size)
	{
		shape = &scene->objects->arr[i];
		t = shape->methods->intersect(shape->obj, o, direction);
		if (t < mn && t > 0)
		{
			mn = t;
			best = shape;
		}
		i++;
	}
	if (best)
		*p = ray_at(mn, direction, o);
	return (best);
}

int	is_shadow(t_vec3 o, t_vec3 d, t_scene *scene, float len)
{
	int		i;
	float	t;
	float	mn;
	t_shape	*shape;

	mn = INFINITY;
	i = 0;
	while (i < scene->objects->size)
	{
		shape = &scene->objects->arr[i];
		t = shape->methods->intersect(shape->obj, o, d);
		if (t > 0 && t < mn)
			mn = t;
		if (mn < len)
			return (1);
		i++;
	}
	return (0);
}

t_vec3	clamp(t_vec3 v)
{
	v.x = fmin(v.x, 255.2);
	v.y = fmin(v.y, 255.2);
	v.z = fmin(v.z, 255.2);
	v.x = fmax(v.x, 0);
	v.y = fmax(v.y, 0);
	v.z = fmax(v.z, 0);
	return (v);
}

t_vec3	cvec(float f)
{
	return ((t_vec3){f, f, f});
}

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

	x = 0;
	while (x < ctx->win_w)
	{
		y = 0;
		while (y < ctx->win_h)
		{
			index = y * ctx->win_w + x;
			direction = calc_direction(x, y, ctx->scene->fov,
					ctx->scene->camera, ctx->win_w, ctx->win_h);
			if (ctx->control.path_tracing)
				color = shade_path(direction, ctx->scene->camera.o,
						ctx->scene, N_BOUNCES);
			else
				color = shade_ray(direction, ctx->scene->camera.o,
						ctx->scene);
			ctx->img_vec[index] = add(ctx->img_vec[index], color);
			y++;
		}
		x++;
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

/*
trace:
Allocate the buffer with dimensions ctx->win_w * ctx->win_h.
Enter an infinite loop calling update_show.
*/
void	trace(t_ctx *ctx)
{
	ctx->rounds = 0;
	ctx->img_vec = ft_calloc(ctx->win_w * ctx->win_h, sizeof(t_vec3));
	if (!ctx->img_vec)
	{
		printf("Errore nell'allocazione di img_vec\n");
		exit(1);
	}
	while (1)
	{
		update_show(ctx);
		printf("Round %d\n", ctx->rounds);
	}
}
