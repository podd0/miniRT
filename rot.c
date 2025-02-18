/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:02:15 by apuddu            #+#    #+#             */
/*   Updated: 2025/02/06 22:53:40 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <libft.h>
#include <math.h>

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
