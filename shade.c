/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:01:30 by amema             #+#    #+#             */
/*   Updated: 2025/03/13 17:17:19 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static t_vec3	compute_light(t_light *light, t_vec3 p,
	t_vec3 normal, t_scene *scene)
{
	t_vec3	v;
	float	dist;
	t_vec3	light_contribute;

	v = sub(light->pos, p);
	dist = vec_length(v);
	if (is_shadow(p, norm(v, 1.0), scene, dist))
		light_contribute = (t_vec3){0, 0, 0};
	else
		light_contribute = scale(3 / (dist * dist)
				* fmax(0, dot(v, normal)), light->color);
	return (light_contribute);
}

t_vec3	lights(t_vec3 p, t_vec3 normal, t_scene *scene)
{
	int		i;
	t_vec3	total_light;
	t_vec3	tmp;

	i = 0;
	total_light = (t_vec3){0, 0, 0};
	while (i < scene->lights->size)
	{
		tmp = compute_light(scene->lights->arr[i], p, normal,
				scene);
		total_light = add(total_light, tmp);
		i++;
	}
	return (total_light);
}

t_vec3	lambert_rebound(t_vec3 normal)
{
	t_vec3	random;

	random.x = drand48() - 0.5;
	random.y = drand48() - 0.5;
	random.z = drand48() - 0.5;
	random = norm(random, 1);
	return (add(normal, random));
}

t_vec3	shade_path(t_vec3 direction, t_vec3 o, t_scene *scene, int depth)
{
	t_vec3	normal;
	t_shape	*shape;
	t_vec3	p;
	t_vec3	color;
	t_vec3	rebound;

	shape = intersect_scene(&p, direction, scene, o);
	if (shape == NULL)
		return (scene->ambient_color);
	normal = shape->methods->normal(shape->obj, p);
	if (dot(normal, direction) > 0)
		normal = neg(normal);
	p = add(scale(EPS, normal), p);
	color = lights(p, normal, scene);
	if (depth == 0)
		return (color);
	rebound = lambert_rebound(normal);
	color = add(color, shade_path(rebound, p, scene, depth - 1));
	return (pairwise_mul(color, shape->color));
}

t_vec3	shade_ray(t_vec3 direction, t_vec3 o, t_scene *scene)
{
	t_vec3	normal;
	t_shape	*shape;
	t_vec3	p;
	t_vec3	color;

	shape = intersect_scene(&p, direction, scene, o);
	if (shape == NULL)
		return (scene->ambient_color);
	normal = shape->methods->normal(shape->obj, p);
	if (dot(normal, direction) > 0)
		normal = neg(normal);
	p = add(scale(EPS, normal), p);
	color = lights(p, normal, scene);
	color = add(color, scene->ambient_color);
	return (pairwise_mul(color, shape->color));
}
