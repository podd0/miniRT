/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:09:20 by amema             #+#    #+#             */
/*   Updated: 2025/03/12 11:54:36 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	intersect_circle(t_cylinder *cy, t_vec3 direction, t_vec3 v)
{
	float	c;
	int		num_solutions;
	float	solutions[2];

	direction.z = 0;
	v.z = 0;
	c = dot(v, v) - (cy->radius * cy->radius);
	num_solutions = solve_quadratic(dot(direction, direction),
			2 * dot(direction, v), c, solutions);
	if (num_solutions == 0)
		return (INFINITY);
	if (num_solutions == 1)
		return (solutions[0]);
	if (solutions[0] > 0 && solutions[1] > 0)
		return (fmin(solutions[0], solutions[1]));
	return (fmax(solutions[0], solutions[1]));
}

float	intersect_sphere(t_sphere *s, t_vec3 origin, t_vec3 direction)
{
	t_vec3	closest;
	float	t;
	float	short_side;
	float	squared_radius;
	float	other_side;

	t = dot(direction, sub(s->center, origin));
	closest = add(origin, scale(t, direction));
	short_side = vec_length(sub(closest, s->center));
	if (fabs(short_side - s->radius) < 1e-5)
		return (t);
	short_side *= short_side;
	squared_radius = s->radius * s->radius;
	if (short_side > squared_radius)
		return (INFINITY);
	other_side = sqrt(squared_radius - short_side);
	if (t - other_side > 0)
		return (t - other_side);
	t += other_side;
	return (t);
}

t_vec3	sphere_normal(t_sphere *s, t_vec3 point)
{
	return (scale(1 / s->radius, sub(point, s->center)));
}
