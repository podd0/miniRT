/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:31:28 by amema             #+#    #+#             */
/*   Updated: 2025/03/13 16:50:48 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_shape	parse_sphere(char **args, int *fail, t_methods *methods)
{
	t_sphere	*sphere;
	t_shape		shape;

	ft_bzero(&shape, sizeof(t_shape));
	if (arg_len(args) != 4)
	{
		*fail = 1;
		return (shape);
	}
	sphere = malloc(sizeof(t_sphere));
	sphere->center = parse_vec(args[1], fail);
	sphere->radius = parse_float(args[2], fail) / 2;
	shape.color = scale(1.0 / 255.0, parse_vec(args[3], fail));
	shape.obj = (void *)sphere;
	shape.methods = methods;
	return (shape);
}

t_shape	parse_plane(char **args, int *fail, t_methods *methods)
{
	t_plane	*plane;
	t_vec3	point;
	t_shape	shape;

	ft_bzero(&shape, sizeof(t_shape));
	if (arg_len(args) != 4)
	{
		*fail = 1;
		return (shape);
	}
	plane = malloc(sizeof(t_plane));
	plane->normal = parse_vec(args[2], fail);
	point = parse_vec(args[1], fail);
	plane->normal = norm(plane->normal, 1.0);
	plane->offset = dot(plane->normal, point);
	shape.color = scale(1.0 / 255.0, parse_vec(args[3], fail));
	shape.obj = (void *)plane;
	shape.methods = methods;
	return (shape);
}

/* var *cy = cylinder (t_cylinder) */
t_shape	parse_cylinder(char **args, int *fail, t_methods *methods)
{
	t_cylinder	*cy;
	t_vec3		center;
	t_vec3		axis;
	float		len;
	t_shape		shape;

	ft_bzero(&shape, sizeof(t_shape));
	if (arg_len(args) != 6)
	{
		*fail = 1;
		return (shape);
	}
	cy = malloc(sizeof(t_cylinder));
	center = parse_vec(args[1], fail);
	axis = norm(parse_vec(args[2], fail), 1.0);
	cy->radius = parse_float(args[3], fail);
	len = parse_float(args[4], fail);
	cy->a = add(center, scale(-len * 0.5, axis));
	cy->b = add(center, scale(len * 0.5, axis));
	cy->height = len;
	cy->fr = z_collinear_to_vec(sub(cy->b, cy->a), cy->a);
	shape.color = scale(1.0 / 255.0, parse_vec(args[5], fail));
	shape.obj = cy;
	shape.methods = methods;
	return (shape);
}

int	parse_object(t_scene *scene, char **args)
{
	int	fail;

	fail = 0;
	if (ft_strncmp(args[0], "sp", 3) == 0)
	{
		vshape_push_back(scene->objects,
			parse_sphere(args, &fail, &scene->methods[SPHERE]));
	}
	else if (ft_strncmp(args[0], "pl", 3) == 0)
	{
		vshape_push_back(scene->objects,
			parse_plane(args, &fail, &scene->methods[PLANE]));
	}
	else if (ft_strncmp(args[0], "cy", 3) == 0)
	{
		vshape_push_back(scene->objects,
			parse_cylinder(args, &fail, &scene->methods[CYLINDER]));
	}
	else
		return (1);
	return (fail);
}

int	parse_element(t_scene *scene, char **args)
{
	int	fail;

	fail = 0;
	if (args[0] == NULL)
		return (0);
	if (ft_toupper(args[0][0]) == args[0][0])
	{
		if (ft_strncmp("A", args[0], 2) == 0)
		{
			scene->ambient_color = parse_ambient(args, &fail);
			scene->flags |= AMBIENT_PARSED;
			return (fail);
		}
		else if (ft_strncmp("C", args[0], 2) == 0)
		{
			scene->flags |= CAMERA_PARSED;
			return (parse_camera(scene, args));
		}
		else if (ft_strncmp("L", args[0], 2) == 0)
			return (parse_light(scene->lights, args));
		else
			return (1);
	}
	return (parse_object(scene, args));
}
