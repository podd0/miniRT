/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:18:20 by apuddu            #+#    #+#             */
/*   Updated: 2025/02/25 17:09:12 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <stdio.h> // per debug

// calc_direction: riceve le dimensioni dinamiche (ctx->win_w, ctx->win_h) come argomenti,
t_vec3	calc_direction(int x, int y, float fov, t_frame camera, int win_w, int win_h)
{
	float	unit_rot;
	t_vec3	v;
	float	dx;
	float	dy;

	dx = drand48() - 0.5;
	dy = drand48() - 0.5;

	// Centra il pixel con i valori dinamici
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
	{
		*p = ray_at(mn, direction, o);
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

t_vec3 aces_tone_mapping(t_vec3 color)
{
	t_vec3 numerator;
	t_vec3 denominator;
	t_vec3 res;
	
	numerator = pairwise_mul(color, add(scale(ACES_A, color), cvec(ACES_B)));
	denominator = add(pairwise_mul(color, add(scale(ACES_C, color), cvec(ACES_D))), cvec(ACES_E));
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
Using: ctx->win_w e ctx->win_h invece delle macro 
Calcola l'indice come y * ctx->win_w + x per accedere a img_vec
Usa calc_direction con i par dinamici
*/
void	update_image(t_ctx *ctx)
{
	int		x, y;
	int		index;
	t_vec3	direction;
	t_vec3	color;

	// printf("update_image: win_w=%d, win_h=%d, total=%d, img_vec=%p\n",
		// ctx->win_w, ctx->win_h, ctx->win_w * ctx->win_h, (void *)ctx->img_vec);

	for (x = 0; x < ctx->win_w; x++)
	{
		for (y = 0; y < ctx->win_h; y++)
		{
			index = y * ctx->win_w + x;
			// calcolo della direzione con dimensioni dinamiche
			direction = calc_direction(x, y, ctx->scene->fov, ctx->scene->camera,
			                           ctx->win_w, ctx->win_h);

			// calcolo del colore (shade_ray o shade_path)
			if (ctx->control.path_tracing)
				color = shade_path(direction, ctx->scene->camera.o, ctx->scene, N_BOUNCES);
			else 
				color = shade_ray(direction, ctx->scene->camera.o, ctx->scene);

			// aggiorno il buffer
			ctx->img_vec[index] = add(ctx->img_vec[index], color);
		}
	}
}

/*
show_image:
ctx->win_w e ctx->win_h per iterare, e calcola l'indice come y * ctx->win_w + x.
than tone mapping + pixel_put.
*/
void	show_image(t_ctx *ctx, int rounds)
{
	int		x, y, index;
	t_vec3	color;

	for (x = 0; x < ctx->win_w; x++)
	{
		for (y = 0; y < ctx->win_h; y++)
		{
			index = y * ctx->win_w + x;
			color = scale(1.0/rounds, ctx->img_vec[index]);
			color = aces_tone_mapping(color);
			pixel_put(ctx->img, x, y, color);
		}
	}
	mlx_put_image_to_window(ctx->mlx, ctx->mlx_win, ctx->img->img, 0, 0);
}

/*
** update_show:
** Aumenta rounds, chiama update_image e poi show_image.
*/
void	update_show(t_ctx *ctx)
{
	ctx->rounds += 1;
	update_image(ctx);
	show_image(ctx, ctx->rounds);
}

/*
** trace:
** Alloca il buffer con dimensioni ctx->win_w * ctx->win_h.
** Entra in un loop infinito chiamando update_show.
*/
void	trace(t_ctx *ctx)
{
	ctx->rounds = 0;
	ctx->img_vec = ft_calloc(ctx->win_w * ctx->win_h, sizeof(t_vec3));
	if (!ctx->img_vec) {
		printf("Errore nell'allocazione di img_vec\n");
		exit(1);
	}
	while (1)
	{
		update_show(ctx); 
		printf("Round %d\n", ctx->rounds);
	}
}
