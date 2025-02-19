/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:18:20 by apuddu            #+#    #+#             */
/*   Updated: 2025/02/19 13:07:47 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vec3	calc_direction(int x, int y, float fov, t_frame camera)
{
	float	unit_rot;
	t_vec3	v;
	float	dx;
	float	dy;

	dx = drand48() - 0.5;
	dy = drand48() - 0.5;
	x -= WIN_W / 2;
	y -= WIN_H / 2;
	unit_rot = fov / WIN_W;
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
	if(best)
	{
		*p = ray_at(mn, direction, o);
		// t_sphere *sp = best->obj;
		// printf("Error = %f\n", vec_length(sub(*p, sp->center)) - sp->radius);
	}
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
		if (t > 0 && t < mn )
			mn = t;
		if (mn < len)
		{
			return (1);
		}
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

t_vec3 aces_tone_mapping(t_vec3 color) {

	t_vec3	numerator;
	t_vec3	denominator;
	t_vec3	res;
	
	numerator = pairwise_mul(color, add(scale(ACES_A, color), cvec(ACES_B)));
	denominator = add(pairwise_mul(color, add(scale(ACES_C, color), cvec(ACES_D))), cvec(ACES_E));
	res = scale(255, pairwise_div(numerator, denominator));
	return (clamp(res));
}

t_vec3	tone_map(t_vec3 v)
{
	// v = scale(1.0/255, v);
	v.x /= v.x+1;
	v.y /= v.y+1;
	v.z /= v.z+1;
	v = scale(255, v);

	return (v);
}

void	update_image(t_ctx *ctx)
{
	int		x;
	int		y;
	t_vec3	direction;
	t_vec3	color;

	x = 0;
	while (x < WIN_W)
	{
		y = 0;
		while (y < WIN_H)
		{
			direction = calc_direction(x, y, ctx->scene->fov, ctx->scene->camera);
			if (ctx->control.path_tracing)
				color = shade_path(direction, ctx->scene->camera.o, ctx->scene, N_BOUNCES);
			else 
				color = shade_ray(direction, ctx->scene->camera.o, ctx->scene);
			ctx->img_vec[x*WIN_H + y] = add(ctx->img_vec[x*WIN_H + y], color);
			y++;
		}
		x++;
	}
}

void	show_image(t_ctx *ctx, int rounds)
{
	t_vec3	color;
	int		x;
	int		y;

	x = 0;
	while (x < WIN_W)
	{
		y = 0;
		while (y < WIN_H)
		{
			color = scale(1.0/rounds, ctx->img_vec[x*WIN_H + y]);
			color = aces_tone_mapping(color);
			pixel_put(ctx->img, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, ctx->img->img, 0, 0);
}

void	update_show(t_ctx *ctx)
{
	ctx->rounds += 1;
	update_image(ctx);
	show_image(ctx, ctx->rounds);
}

void	trace(t_ctx *ctx)
{
	ctx->rounds = 0;
	ctx->img_vec = ft_calloc(WIN_H * WIN_W, sizeof(t_vec3));

	while (1)
	{
		update_show(ctx); 
		printf("Round %d\n", ctx->rounds);
	}
}

