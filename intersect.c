#include <rt.h>

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

float	intersect_plane(t_plane *pl, t_vec3 origin, t_vec3 direction)
{
	float	d_norm;
	float	temp;

	d_norm = dot(direction, pl->normal);
	if (d_norm == 0)
	{
		return (INFINITY);
	}
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

float	intersect_circle(t_cylinder *cy, t_vec3 direction, t_vec3 v)
{
	float	c;
	int		num_solutions;
	float	solutions[2];

	direction.z = 0;
	v.z = 0;
	c = dot(v, v) - (cy->radius * cy->radius);
	num_solutions = solve_quadratic(dot(direction, direction), 2
			* dot(direction, v), c, solutions);
	if (num_solutions == 0)
		return (INFINITY);
	if (num_solutions == 1)
		return (solutions[0]);
	if (solutions[0] > 0 && solutions[1] > 0)
		return (fmin(solutions[0], solutions[1]));
	return (fmax(solutions[0], solutions[1]));
}

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
	if (f > 0 && vec_length(sub(ray_at(f, direction, origin),
				cy->a)) < cy->radius)
		res = f;
	// return (res);
	pl.offset = dot(pl.normal, cy->b);
	f = intersect_plane(&pl, origin, direction);
	if (f > 0 && vec_length(sub(ray_at(f, direction, origin),
				cy->b)) < cy->radius)
		res = fminf(res, f);
	return (res);
}

float	intersect_cylinder(t_cylinder *cy, t_vec3 origin, t_vec3 direction)
{
	float	f;
	float	fc;

	f = intersect_cylinder_side(cy, origin, direction);
	fc = f;
	f = fminf(f, intersect_cylinder_base(cy, origin, direction));
	// if (fc == f)
	// {
	// 	printf("SIDE\n");
	// }
	// else
	// 	printf("BASE\n");
	return (f);
}

t_vec3	cylinder_normal(t_cylinder *cy, t_vec3 point)
{
	point = to_frame(point, cy->fr);
	if (point.z < 1e-5)
	{
		return (neg(cy->fr.z));
	}
	if (point.z > cy->height - 1e-5)
	{
		return (cy->fr.z);
	}
	point.z = 0;
	return (norm(v_to_world(point, cy->fr), 1.0));
}
