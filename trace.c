/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:23:36 by amema             #+#    #+#             */
/*   Updated: 2025/03/13 19:02:26 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

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
