/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:23:09 by amema             #+#    #+#             */
/*   Updated: 2025/03/12 11:26:45 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	calc_direction(t_screen screen, float fov, t_frame camera)
{
	float	unit_rot;
	t_vec3	v;
	float	dx;
	float	dy;

	dx = drand48() - 0.5;
	dy = drand48() - 0.5;
	screen.x -= screen.win_w / 2;
	screen.y -= screen.win_h / 2;
	unit_rot = fov / max(screen.win_h, screen.win_w);
	v = rotx((dy + screen.y) * unit_rot).z;
	v = to_world(v, roty((dx + screen.x) * unit_rot));
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
