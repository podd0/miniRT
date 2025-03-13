/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:13:05 by amema             #+#    #+#             */
/*   Updated: 2025/03/13 16:57:24 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

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
	methods[SPHERE].intersect = (float (*)(void *, t_vec3, t_vec3))
		intersect_sphere;
	methods[PLANE].intersect = (float (*)(void *, t_vec3, t_vec3))
		intersect_plane;
	methods[CYLINDER].intersect = (float (*)(void *, t_vec3, t_vec3))
		intersect_cylinder;
	methods[SPHERE].normal = (t_vec3 (*)(void *, t_vec3))sphere_normal;
	methods[PLANE].normal = (t_vec3 (*)(void *, t_vec3))plane_normal;
	methods[CYLINDER].normal = (t_vec3 (*)(void *, t_vec3))cylinder_normal;
	methods[SPHERE].move = (void (*)(void *, t_vec3))move_sphere;
	methods[PLANE].move = (void (*)(void *, t_vec3))move_plane;
	methods[CYLINDER].move = (void (*)(void *, t_vec3))move_cylinder;
	methods[PLANE].rotate = (void (*)(void *obj, t_frame rot))rotate_plane;
	methods[SPHERE].rotate = (void (*)(void *obj, t_frame rot))rotate_sphere;
	methods[CYLINDER].rotate = (void (*)
			(void *obj, t_frame rot))rotate_cylinder;
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
	if (scene->flags != 3)
	{
		ft_putstr_fd("Missing camera or ambient light\n", 2);
		free_scene(scene);
		return (NULL);
	}
	return (scene);
}
