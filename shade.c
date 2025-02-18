/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 00:49:10 by apuddu            #+#    #+#             */
/*   Updated: 2025/02/18 12:22:02 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>



t_vec3	lights(t_vec3 p, t_vec3 normal, t_scene *scene)
{
	int		i;
	t_light	*light;
	t_vec3	total_light;
	t_vec3	light_contribute;
	t_vec3	v;
	float	dist;

	i = 0;
	total_light = (t_vec3){0, 0, 0};
	while (i < scene->lights->size)
	{
		light = scene->lights->arr[i];
		v = sub(light->pos, p);
		dist = vec_length(v);
		if (!is_shadow(p, norm(v, 1.0), scene, dist))
		{
			light_contribute = scale(3/(dist * dist) * fmax(0, dot(v, normal)), light->color);
			// light_contribute = light->color;
			total_light = add(total_light, light_contribute);
		}
		i++;
	}
	return (total_light);
}

t_vec3	lambert_rebound(t_vec3 normal)
{
	t_vec3	random;

	random.x = drand48() -0.5;
	random.y = drand48() -0.5;
	random.z = drand48() -0.5;
	random = norm(random, 1);
	return add(normal, random);
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
	{
		return (scene->ambient_color);
	}
	normal = shape->methods->normal(shape->obj, p);
	if (dot(normal, direction) > 0)
		normal = neg(normal);
	p = add(scale(3e-5, normal), p);
	color = lights(p, normal, scene);
	if (depth == 0)
		return (color);
	rebound = lambert_rebound(normal);
	color = add(color, shade_path(rebound, p, scene, depth - 1));
	return (pairwise_mul(color,  shape->color));
}


t_vec3	shade_ray(t_vec3 direction, t_vec3 o, t_scene *scene)
{
	t_vec3	normal;
	t_shape	*shape;
	t_vec3	p;
	t_vec3	color;

	shape = intersect_scene(&p, direction, scene, o);
	if (shape == NULL)
	{
		return (scene->ambient_color);
	}
	normal = shape->methods->normal(shape->obj, p);
	if (dot(normal, direction) > 0)
		normal = neg(normal);
	p = add(scale(3e-5, normal), p);
	color = lights(p, normal, scene);
	color = add(color,  scene->ambient_color);
	return (pairwise_mul(color,  shape->color));
}
