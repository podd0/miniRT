/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:32:31 by amema             #+#    #+#             */
/*   Updated: 2025/03/13 19:02:00 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

float	deg_to_rad(float degrees)
{
	return (degrees / 180 * M_PI);
}

t_frame	rotx(float degrees)
{
	float	rads;
	t_frame	res;

	rads = deg_to_rad(degrees);
	res.o = (t_vec3){0., 0., 0.};
	res.x = (t_vec3){1., 0., 0.};
	res.y = (t_vec3){0., cosf(rads), -sinf(rads)};
	res.z = (t_vec3){0., sinf(rads), cosf(rads)};
	return (res);
}

t_frame	roty(float degrees)
{
	float	rads;
	t_frame	res;

	rads = deg_to_rad(degrees);
	res.o = (t_vec3){0., 0., 0.};
	res.x = (t_vec3){cosf(rads), 0., sinf(rads)};
	res.y = (t_vec3){0., 1., 0.};
	res.z = (t_vec3){-sinf(rads), 0., cosf(rads)};
	return (res);
}

t_frame	rotz(float degrees)
{
	float	rads;
	t_frame	res;

	rads = deg_to_rad(degrees);
	res.o = (t_vec3){0., 0., 0.};
	res.x = (t_vec3){cosf(rads), -sinf(rads), 0.};
	res.y = (t_vec3){sinf(rads), cosf(rads), 0.};
	res.z = (t_vec3){0., 0., 1.};
	return (res);
}
