/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:01:42 by amema             #+#    #+#             */
/*   Updated: 2025/03/10 17:07:24 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void translate_light(t_light *light, t_vec3 delta)
{
	light->pos = add(light->pos, delta);
}

// approach1: rotate a light around the world origin (0, 0, 0)
void rotate_light(t_light *light, t_frame rot)
{
	t_vec3 new_pos = v_to_world(light->pos, rot);
	light->pos = new_pos;
}

// approach2: rotate a light around a pivot point
// This fun rotates a light around a given pivot point using a specified rotation.
// ex: light(5, 0, 0) && pivot @ (0, 0, 0) -> rot by 90 around z-ax -> result: will move light to (0, 5, 0).

void rotate_light_pivot(t_light *light, t_frame rot, t_vec3 pivot)
{
	t_vec3 rel = sub(light->pos, pivot); // calc relative vector pivot -> light
	rel = v_to_world(rel, rot); // rotare relative vector
	light->pos = add(pivot, rel);		 // update light position by adding the pivot to the rotated vector
}
