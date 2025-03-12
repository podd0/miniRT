/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:07:42 by amema             #+#    #+#             */
/*   Updated: 2025/03/12 11:14:40 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	intersect_cylinder_side(t_cylinder *cy, t_vec3 origin, t_vec3 direction)
{
	float	t;
	t_vec3	v;
	t_vec3	inters;

	direction = v_to_frame(direction, cy->fr);
	v = to_frame(origin, cy->fr);
	t = intersect_circle(cy, direction, v);
	if (t == INFINITY || t < 0)
		return (INFINITY);
	inters = ray_at(t, direction, v);
	if (inters.z > cy->height || inters.z < 0)
		return (INFINITY);
	return (t);
}

float	intersect_cylinder_base(t_cylinder *cy, t_vec3 origin, t_vec3 direction)
{
	float	f;
	float	res;
	t_plane	pl;

	res = INFINITY;
	pl.normal = norm(sub(cy->b, cy->a), 1.0);
	pl.offset = dot(pl.normal, cy->a);
	f = intersect_plane(&pl, origin, direction);
	if (f > 0 && vec_length(sub(ray_at(f, direction, origin), cy->a))
		< cy->radius)
		res = f;
	pl.offset = dot(pl.normal, cy->b);
	f = intersect_plane(&pl, origin, direction);
	if (f > 0 && vec_length(sub(ray_at(f, direction, origin), cy->b))
		< cy->radius)
		res = fminf(res, f);
	return (res);
}

float	intersect_cylinder(t_cylinder *cy, t_vec3 origin, t_vec3 direction)
{
	float	f;

	f = intersect_cylinder_side(cy, origin, direction);
	f = fminf(f, intersect_cylinder_base(cy, origin, direction));
	return (f);
}

t_vec3	cylinder_normal(t_cylinder *cy, t_vec3 point)
{
	point = to_frame(point, cy->fr);
	if (point.z < 1e-5)
		return (neg(cy->fr.z));
	if (point.z > cy->height - 1e-5)
		return (cy->fr.z);
	point.z = 0;
	return (norm(v_to_world(point, cy->fr), 1.0));
}
