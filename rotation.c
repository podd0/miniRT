/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:33:03 by amema             #+#    #+#             */
/*   Updated: 2025/03/13 17:58:33 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	rotate_plane(t_plane *pl, t_frame rot)
{
	t_vec3	pivot;
	t_vec3	new_normal;
	t_vec3	new_pivot;
	float	new_offset;

	pivot = scale(pl->offset, pl->normal);
	new_normal = v_to_world(pl->normal, rot);
	new_normal = norm(new_normal, 1.0f);
	new_pivot = v_to_world(pivot, rot);
	new_offset = dot(new_normal, new_pivot);
	pl->normal = new_normal;
	pl->offset = new_offset;
}

void	rotate_cylinder(t_cylinder *cy, t_frame rot)
{
	t_vec3	center;
	t_vec3	a_rel;
	t_vec3	b_rel;

	center = scale(0.5f, add(cy->a, cy->b));
	a_rel = sub(cy->a, center);
	b_rel = sub(cy->b, center);
	a_rel = v_to_world(a_rel, rot);
	b_rel = v_to_world(b_rel, rot);
	cy->a = add(center, a_rel);
	cy->b = add(center, b_rel);
	cy->fr = z_collinear_to_vec(sub(cy->b, cy->a), cy->a);
}

void	rotate_sphere(t_sphere *sp, t_frame rot)
{
	(void)sp;
	(void)rot;
	return ;
}

void	rotate_camera(t_frame *cam, t_frame rot)
{
	t_frame	cam_copy;

	cam_copy = *cam;
	cam->x = v_to_world(rot.x, cam_copy);
	cam->y = v_to_world(rot.y, cam_copy);
	cam->z = v_to_world(rot.z, cam_copy);
	cam->x = norm(cam->x, 1.0f);
	cam->y = norm(cam->y, 1.0f);
	cam->z = norm(cam->z, 1.0f);
}
