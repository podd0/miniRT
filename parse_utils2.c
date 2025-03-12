/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:29:16 by amema             #+#    #+#             */
/*   Updated: 2025/03/12 11:34:12 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	parse_ambient(char **args, int *fail)
{
	float	f;
	t_vec3	res;

	if (arg_len(args) != 3)
	{
		*fail = 1;
		return ((t_vec3){0, 0, 0});
	}
	f = parse_float(args[1], fail);
	if (f < 0 || f > 1)
	{
		*fail = 1;
		return ((t_vec3){0, 0, 0});
	}
	res = parse_vec(args[2], fail);
	return (scale(1.0 / 255.0 * f, res));
}

void	set_xy_from_z(t_frame *camera_frame)
{
	t_vec3	up;

	if (camera_frame->z.x == 0.0 && camera_frame->z.z == 0.0)
	{
		camera_frame->x = (t_vec3){1, 0, 0};
		if (camera_frame->z.y > 0)
		{
			camera_frame->y = (t_vec3){0, 0, -1};
		}
		else
		{
			camera_frame->y = (t_vec3){0, 0, 1};
		}
	}
	else
	{
		up = (t_vec3){0, 1, 0};
		camera_frame->x = norm(cross(up, camera_frame->z), 1.0);
		camera_frame->y = norm(cross(camera_frame->z, camera_frame->x), 1.0);
	}
}

int	parse_camera(t_scene *scene, char **args)
{
	int	fail;

	fail = 0;
	if (arg_len(args) != 4)
		return (1);
	scene->camera.o = parse_vec(args[1], &fail);
	scene->camera.z = norm(parse_vec(args[2], &fail), 1);
	scene->fov = parse_float(args[3], &fail);
	set_xy_from_z(&scene->camera);
	return (fail);
}

int	parse_light(t_vector *lights, char **args)
{
	t_light	*light;
	int		fail;

	fail = 0;
	if (arg_len(args) != 4)
		return (1);
	light = malloc(sizeof(t_light));
	light->pos = parse_vec(args[1], &fail);
	light->color = parse_vec(args[3], &fail);
	light->color = scale(1.0 / 255.0 * parse_float(args[2], &fail),
			light->color);
	vec_push_back(lights, light);
	return (fail);
}
