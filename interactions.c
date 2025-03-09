/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 00:25:38 by apuddu            #+#    #+#             */
/*   Updated: 2025/02/25 13:35:00 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	move_sphere(t_sphere *sp, t_vec3 delta)
{
	sp->center = add(delta, sp->center);
}

void	move_plane(t_plane *pl, t_vec3 delta)
{
	pl->offset += dot(delta, pl->normal);
}

void	move_cylinder(t_cylinder *cy, t_vec3 delta)
{
	cy->a = add(cy->a, delta);
	cy->b = add(cy->b, delta);
	cy->fr.o = add(cy->fr.o, delta);
}
