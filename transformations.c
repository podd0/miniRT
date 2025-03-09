/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:09:59 by amema             #+#    #+#             */
/*   Updated: 2025/03/09 18:56:57 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void resize_sphere(t_sphere *sp, float delta_diameter)
{
    float new_diameter = (sp->radius * 2.0f) + delta_diameter;
    if (new_diameter < 0.1f)
        new_diameter = 0.1f;
    sp->radius = new_diameter / 2.0f;
}

void resize_cylinder_diameter(t_cylinder *cy, float delta_diameter)
{
    float new_diameter = (cy->radius * 2.0f) + delta_diameter;
    if (new_diameter < 0.1f)
        new_diameter = 0.1f;
    cy->radius = new_diameter / 2.0f;
}


void resize_cylinder_height(t_cylinder *cy, float delta_height)
{
    float new_height = cy->height + delta_height;
    if (new_height < 0.1f)
        new_height = 0.1f;
    cy->height = new_height;
    t_vec3 center = scale(0.5f, add(cy->a, cy->b));
    t_vec3 axis = norm(sub(cy->b, cy->a), 1.0f);
    cy->a = add(center, scale(-new_height / 2.0f, axis));
    cy->b = add(center, scale(new_height / 2.0f, axis));
    cy->fr = z_collinear_to_vec(sub(cy->b, cy->a), cy->a);
}
