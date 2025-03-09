/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:33:03 by amema             #+#    #+#             */
/*   Updated: 2025/03/09 20:22:47 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

// ruota il piano attorno a (normal * offset)
void rotate_plane(t_plane *pl, t_frame rot)
{
    printf("Rotazione piano\n");
    t_vec3 pivot = scale(pl->offset, pl->normal);
    t_vec3 new_normal = v_to_world(pl->normal, rot);
    new_normal = norm(new_normal, 1.0f);
    t_vec3 new_pivot = v_to_world(pivot, rot);
    float new_offset = dot(new_normal, new_pivot);
    pl->normal = new_normal;
    pl->offset = new_offset;
}

// ruota il cl attorno al suo c aggiornando estremi e frame
void rotate_cylinder(t_cylinder *cy, t_frame rot)
{
    printf("Rotazione cilindro\n");
    t_vec3 center = scale(0.5f, add(cy->a, cy->b));
    t_vec3 a_rel = sub(cy->a, center);
    t_vec3 b_rel = sub(cy->b, center);
    a_rel = v_to_world(a_rel, rot);
    b_rel = v_to_world(b_rel, rot);
    cy->a = add(center, a_rel);
    cy->b = add(center, b_rel);
    cy->fr = z_collinear_to_vec(sub(cy->b, cy->a), cy->a);
}

void rotate_sphere(t_sphere *sp, t_frame rot)
{
    (void)sp;
    (void)rot;
    return ;
}

// ruota il frame della cam applayin rot transform
void rotate_camera(t_frame *cam, t_frame rot)
{
    cam->x = v_to_world(cam->x, rot);
    cam->y = v_to_world(cam->y, rot);
    cam->z = v_to_world(cam->z, rot);
    cam->x = norm(cam->x, 1.0f);
    cam->y = norm(cam->y, 1.0f);
    cam->z = norm(cam->z, 1.0f);
}
