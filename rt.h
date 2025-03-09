/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:35:28 by amema             #+#    #+#             */
/*   Updated: 2025/03/09 21:06:23 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <get_next_line.h>
# include <libft.h>
# include <vector.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <fcntl.h>
# include <unistd.h>

# define WIN_W 1800
# define WIN_H 600
# define N_BOUNCES 2

# define MOVE_SPEED 0.3
# define EPS 5e-5

# define ACES_A 2.51f
# define ACES_B 0.03f
# define ACES_C 2.43f
# define ACES_D 0.59f
# define ACES_E 0.14f

/*
** Structures
*/

struct s_vec3
{
	float	x;
	float	y;
	float	z;
};

typedef struct s_vec3	t_vec3;

struct s_frame
{
	t_vec3	x;
	t_vec3	y;
	t_vec3	z;
	t_vec3	o;
};

typedef struct s_frame	t_frame;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_sphere
{
	t_vec3	center;
	float	radius;
}	t_sphere;

/*
** Plane: represented by its normal (perpendicular vector) and offset
** so that: (point dot normal) = offset.
*/
typedef struct s_plane
{
	t_vec3	normal;
	float	offset;
}	t_plane;

/*
** Cylinder: the axis is the segment [a, b] and for each point on that
** segment the cylinder consists of the circle (of radius `radius`)
** orthogonal to the segment.
*/
typedef struct s_cylinder
{
	t_vec3	a;
	t_vec3	b;
	float	radius;
	float	height;
	t_frame	fr;
}	t_cylinder;

# define SPHERE 0
# define PLANE 1
# define CYLINDER 2

typedef struct s_methods
{
	float	(*intersect)(void *shape, t_vec3 origin, t_vec3 direction);
	t_vec3	(*normal)(void *shape, t_vec3 point);
	void	(*move)(void *shape, t_vec3 delta);
	void	(*rotate)(void *obj, t_frame rot);
}	t_methods;

typedef struct s_shape
{
	void		*obj;
	t_vec3		color;
	t_methods	*methods;
}	t_shape;

struct s_vshape
{
	t_shape	*arr;
	int		size;
	int		buf_size;
};

typedef struct s_vshape	t_vshape;

void		vshape_push_back(t_vshape *vec, t_shape elem);
t_shape		vshape_pop_back(t_vshape *vec);
void		vshape_assign(t_vshape *vec, int n, t_shape value);
void		vshape_resize(t_vshape *vec, int n);
t_vshape	*vshape_init(int n, t_shape value);
t_vshape	*vshape_uninit(int n);
void		vshape_free(t_vshape *vec);
t_vshape	*vshape_copy(t_vshape *vec);
void		vshape_map(t_vshape *vec, void (*f)(t_shape));
void		vshape_map_sub(t_vshape *vec, t_shape (*f)(t_shape));
t_shape		vshape_back(t_vshape *vec);

typedef struct s_light
{
	t_vec3	pos;
	t_vec3	color;
}	t_light;

/*
** Scene: contains the camera, the ambient color,
** the objects and the lights.
*/
typedef struct s_scene
{
	t_frame		camera;
	float		fov;
	t_vec3		ambient_color;
	t_vshape	*objects;
	t_vector	*lights;
	t_methods	methods[4];
}	t_scene;

typedef struct s_control
{
	int		shift;
	int		path_tracing;
	int		space;
	int		reset;
	t_vec3	delta;
}	t_control;

typedef struct s_ctx
{
	t_shape		*selected;
	t_vec3		selection_color;
	t_scene		*scene;
	void		*mlx;
	void		*mlx_win;
	t_img		*img;
	t_vec3		*img_vec;
	int			rounds;
	t_control	control;
	int			win_w; /* current width */
	int			win_h; /* current height */
}	t_ctx;

typedef struct s_screen
{
    int	x;
    int	y;
	int	win_w;
	int	win_h;
}	t_screen;


/*
** Vector math
*/

t_vec3		add(const t_vec3 a, const t_vec3 b);
float		dot(const t_vec3 a, const t_vec3 b);
t_vec3		cross(const t_vec3 a, const t_vec3 b);
t_vec3		neg(const t_vec3 a);
t_vec3		sub(const t_vec3 a, const t_vec3 b);
t_vec3		scale(float f, const t_vec3 v);
t_vec3		norm(t_vec3 v, float target_len);
float		vec_length(t_vec3 v);
t_vec3		pairwise_mul(t_vec3 a, t_vec3 b);
t_vec3		pairwise_div(t_vec3 a, t_vec3 b);
int			max(int a, int b);

/*
** Coordinate transforms
*/
t_vec3		to_frame(t_vec3 p, t_frame fr);
t_vec3		to_world(t_vec3 p, t_frame fr);
float		deg_to_rad(float degrees);
t_frame		rotx(float degrees);
t_frame		roty(float degrees);
t_frame		rotz(float degrees);
t_frame		f_to_world(t_frame f1, t_frame ref);
t_frame		f_to_frame(t_frame f1, t_frame ref);
t_vec3		v_to_frame(t_vec3 p, t_frame fr);
t_vec3		v_to_world(t_vec3 p, t_frame fr);
t_frame		z_collinear_to_vec(t_vec3 z, t_vec3 base);
t_vec3		ray_at(float t, t_vec3 direction, t_vec3 origin);

/*
** Parsing and scene management
*/
t_scene		*parse(char *filename);
void		free_scene(t_scene *scene);
t_ctx		init(char *filename);

/*
** Drawing
*/
void		pixel_put(t_img *img, int x, int y, t_vec3 color);

/*
** Intersection and normals
*/
float		intersect_sphere(t_sphere *s, t_vec3 origin, t_vec3 direction);
t_vec3		sphere_normal(t_sphere *s, t_vec3 point);
float		intersect_plane(t_plane *pl, t_vec3 origin, t_vec3 direction);
t_vec3		plane_normal(t_plane *pl, t_vec3 point);
float		intersect_cylinder(t_cylinder *cy, t_vec3 origin, t_vec3 direction);
t_vec3		cylinder_normal(t_cylinder *cy, t_vec3 point);
t_vec3		norm_color(t_vec3 color);

/*
** Ray tracing
*/
void		trace(t_ctx *ctx);
t_vec3		calc_direction(t_screen screen, float fov, t_frame camera);
t_shape		*intersect_scene(t_vec3 *p, t_vec3 direction, t_scene *scene,
				t_vec3 o);
int			is_shadow(t_vec3 o, t_vec3 d, t_scene *scene, float len);
t_vec3		shade_path(t_vec3 direction, t_vec3 o, t_scene *scene, int depth);
t_vec3		shade_ray(t_vec3 direction, t_vec3 o, t_scene *scene);
void		update_show(t_ctx *ctx);
void		pvec(t_vec3 v);

/*
** Event handling and utilities
*/
int			loop(t_ctx *ctx);
int			handle_key_up(int key, t_control *ctrl);
int			handle_key_down(int key, t_ctx *ctx);
int			handle_mouse(int k, int x, int y, t_ctx *ctx);
t_img		*init_image(void *mlx, int win_w, int win_h); /* used in events.c */
void		reset_show(t_ctx *ctx); /* used in events.c */
void		virtual_resize(t_ctx *ctx, int new_w, int new_h);
void		move_sphere(t_sphere *sp, t_vec3 delta);
void		move_plane(t_plane *pl, t_vec3 delta);
void		move_cylinder(t_cylinder *cy, t_vec3 delta);

/*
** Transformations
*/

void resize_sphere(t_sphere *sp, float delta_diameter);
void resize_cylinder_diameter(t_cylinder *cy, float delta_diameter);
void resize_cylinder_height(t_cylinder *cy, float delta_height);

/*
** Rotations
*/
void rotate_plane(t_plane *pl, t_frame rot);
void rotate_cylinder(t_cylinder *cy, t_frame rot);
void rotate_camera(t_frame *cam, t_frame rot);
void rotate_sphere(t_sphere *sp, t_frame rot);

#endif
