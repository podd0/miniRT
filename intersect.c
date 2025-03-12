/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:36:28 by amema             #+#    #+#             */
/*   Updated: 2025/03/12 11:47:14 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	intersect_plane(t_plane *pl, t_vec3 origin, t_vec3 direction)
{
	float	d_norm;
	float	temp;

	d_norm = dot(direction, pl->normal);
	if (d_norm == 0)
		return (INFINITY);
	temp = (pl->offset - dot(origin, pl->normal));
	return (temp / d_norm);
}

t_vec3	plane_normal(t_plane *pl, t_vec3 point)
{
	(void)point;
	return (pl->normal);
}

t_vec3	norm_color(t_vec3 color)
{
	color = scale(128, color);
	color = add((t_vec3){128, 128, 128}, color);
	return (color);
}

t_frame	z_collinear_to_vec(t_vec3 z, t_vec3 base)
{
	t_frame	fr;

	fr.z = norm(z, 1.0);
	fr.o = base;
	if (fr.z.z != 0)
	{
		fr.x.x = 0;
		fr.x.y = 1;
		fr.x.z = -fr.z.y / fr.z.z;
		fr.x = norm(fr.x, 1);
	}
	else
		fr.x = (t_vec3){0, 0, 1};
	fr.y = cross(fr.z, fr.x);
	return (fr);
}

int	solve_quadratic(float a, float b, float c, float sol[2])
{
	float	delta;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	delta = sqrt(delta);
	sol[0] = (-b - delta) / (2 * a);
	sol[1] = (-b + delta) / (2 * a);
	return (2);
}
