/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:59:28 by apuddu            #+#    #+#             */
/*   Updated: 2025/02/12 19:59:00 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int	get_sign(char **str, int *err)
{
	if (!*str)
	{
		*err = 1;
		return (0);
	}
	if (**str == '-')
	{
		(*str)++;
		return (-1);
	}
	if (**str == '+')
		(*str)++;
	return (1);
}

float	get_integer_part(char **str, int *err)
{
	float	res;

	if (*err)
		return (0.0);
	res = 0.0;
	while (**str && **str != '.')
	{
		if (!ft_isdigit(**str))
		{
			*err = 1;
			return (0.0);
		}
		res *= 10;
		res += (**str - '0');
		(*str)++;
	}
	return (res);
}

float	parse_float(char *str, int *err)
{
	float	integer;
	float	frac;
	int		sign;

	if (!str)
		*err = 1;
	if (*err)
		return (0.0);
	sign = get_sign(&str, err);
	integer = get_integer_part(&str, err);
	if (*str == '\0' || *err)
		return (integer * sign);
	str++;
	frac = get_integer_part(&str, err);
	if (*str != '\0')
		*err = 1;
	if (*err)
		return (0.0);
	while (frac >= 1)
		frac /= 10.0;
	return (sign * (integer + frac));
}

// Returns the length of a null-terminated array of strings
int	arg_len(char **arr)
{
	int	l;

	l = 0;
	if (arr == NULL)
		return (-1);
	while (arr[l] != NULL)
	{
		l++;
	}
	return (l);
}

t_vec3	parse_vec(char *s, int *fail)
{
	char	**splitted;
	t_vec3	res;

	if (!s)
	{
		*fail = 1;
		return ((t_vec3){0, 0, 0});
	}
	splitted = ft_split(s, ',');
	*fail = *fail || arg_len(splitted) != 3;
	if (*fail)
	{
		ft_split_free(splitted);
		return ((t_vec3){0, 0, 0});
	}
	res.x = parse_float(splitted[0], fail);
	res.y = parse_float(splitted[1], fail);
	res.z = parse_float(splitted[2], fail);
	ft_split_free(splitted);
	return (res);
}

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
	return (scale(1.0/255.0* f, res));
}

void	set_xy_from_z(t_frame *camera_frame)
{
	t_vec3	up;

	if (camera_frame->z.x == 0.0 &&  camera_frame->z.z == 0.0)
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
	// scene->fov = deg_to_rad(scene->fov);
	set_xy_from_z(&scene->camera);
	return (fail);
}

int parse_light(t_vector *lights, char **args)
{
	t_light	*light;
	int		fail;

	fail = 0;
	if (arg_len(args) != 4)
		return (1);
	light = malloc(sizeof(t_light));
	light->pos = parse_vec(args[1], &fail);
	light->color = parse_vec(args[3], &fail);
	light->color = scale(1.0/255.0 * parse_float(args[2], &fail), light->color);
	vec_push_back(lights, light);
	return (fail);
}

t_shape	parse_sphere(char **args, int *fail, t_methods *methods)
{
	t_sphere	*sphere;
	t_shape		shape;

	ft_bzero(&shape, sizeof(t_shape));
	if(arg_len(args) != 4)
	{
		*fail = 1;
		return (shape);
	}
	sphere = malloc(sizeof(t_sphere));
	sphere->center = parse_vec(args[1], fail);
	sphere->radius = parse_float(args[2], fail) / 2;
	shape.color = scale(1.0/255.0, parse_vec(args[3], fail));
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
	if(arg_len(args) != 4)
	{
		*fail = 1;
		return (shape);
	}
	plane = malloc(sizeof(t_plane));
	plane->normal = parse_vec(args[2], fail);
	point = parse_vec(args[1], fail);
	plane->normal = norm(plane->normal, 1.0);
	plane->offset = dot(plane->normal, point);
	shape.color = scale(1.0/255.0, parse_vec(args[3], fail));
	shape.obj = (void *)plane;
	shape.methods = methods;
	return (shape);
}

t_shape	parse_cylinder(char **args, int *fail, t_methods *methods)
{
	t_cylinder	*cylinder;
	t_vec3	center;
	t_vec3	axis;
	float	len;
	t_shape	shape;

	ft_bzero(&shape, sizeof(t_shape));
	if(arg_len(args) != 6)
	{
		*fail = 1;
		return (shape);
	}
	cylinder = malloc(sizeof(t_cylinder));
	center = parse_vec(args[1], fail);
	axis = norm(parse_vec(args[2], fail), 1.0);
	cylinder->radius = parse_float(args[3], fail);
	len = parse_float(args[4], fail);
	cylinder->a = add(center, scale(-len*0.5, axis));
	cylinder->b = add(center, scale(len*0.5, axis));
	cylinder->height = len;
	cylinder->fr = z_collinear_to_vec(sub(cylinder->b, cylinder->a), cylinder->a);
	shape.color = scale(1.0/255.0, parse_vec(args[5], fail));
	shape.obj = cylinder;
	shape.methods = methods;
	return (shape);
}

int	parse_object(t_scene *scene, char **args)
{
	int	fail;

	fail = 0;
	if (ft_strncmp(args[0], "sp", 3) == 0)
	{
		vshape_push_back(scene->objects, parse_sphere(args, &fail, &scene->methods[SPHERE]));
		
	}
	else if (ft_strncmp(args[0], "pl", 3) == 0)
	{
		vshape_push_back(scene->objects, parse_plane(args, &fail, &scene->methods[PLANE]));
	}
	else if (ft_strncmp(args[0], "cy", 3) == 0)
	{
		vshape_push_back(scene->objects, parse_cylinder(args, &fail, &scene->methods[CYLINDER]));
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
			return (fail);
		}
		else if (ft_strncmp("C", args[0], 2) == 0)
			return (parse_camera(scene, args));
		else if(ft_strncmp("L", args[0], 2) == 0)
			return (parse_light(scene->lights, args));
		else
			return (1);
	}
	return parse_object(scene, args);
}
void	free_shape(t_shape shape)
{
	free(shape.obj);
}

void	free_scene(t_scene *scene)
{
	vshape_map(scene->objects, free_shape);
	vshape_free(scene->objects);
	vec_map(scene->lights, free);
	vec_free(scene->lights);
	free(scene);
}

// initialize scene with the contents of filename and return scene,
// return NULL and free scene on error
t_scene	*parse_init(t_scene *scene, int fd)
{
	char	*line;
	char	**splitted;
	char	*trimmed;

	scene->lights = vec_uninit(0);
	scene->objects = vshape_uninit(0);
	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, "\n ");
		free(line);
		splitted = ft_split(trimmed, ' ');
		if (parse_element(scene, splitted))
		{
			free_scene(scene);
			puts(trimmed);
			ft_split_free(splitted);
			free(trimmed);
			return (NULL);
		}
		free(trimmed);
		ft_split_free(splitted);
		line = get_next_line(fd);
	}
	return (scene);
}

void	set_methods(t_methods *methods)
{
	methods[SPHERE].intersect = (float (*)(void *, t_vec3,  t_vec3))intersect_sphere;
	methods[SPHERE].normal = (t_vec3 (*)(void *, t_vec3)) sphere_normal;
	methods[PLANE].intersect = (float (*)(void *, t_vec3,  t_vec3))intersect_plane;
	methods[PLANE].normal = (t_vec3 (*)(void *, t_vec3)) plane_normal;
	methods[CYLINDER].intersect = (float (*)(void *, t_vec3,  t_vec3))intersect_cylinder;
	methods[CYLINDER].normal = (float (*)(void *, t_vec3,  t_vec3))cylinder_normal;
}

t_scene	*parse(char *filename)
{
	int		fd;
	t_scene	*scene;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (NULL);
	}
	scene = malloc(sizeof(t_scene));
	set_methods(scene->methods);
	scene = parse_init(scene, fd);
	close(fd);
	return (scene);
}
