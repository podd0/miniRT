/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:01:42 by amema             #+#    #+#             */
/*   Updated: 2025/03/12 14:15:36 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	translate_light(t_light *light, t_vec3 delta)
{
	light->pos = add(light->pos, delta);
}

void	rotate_light(t_light *light, t_frame rot)
{
	t_vec3	new_pos;

	new_pos = v_to_world(light->pos, rot);
	light->pos = new_pos;
}

void	rotate_light_pivot(t_light *light, t_frame rot, t_vec3 pivot)
{
	t_vec3	rel;

	rel = sub(light->pos, pivot);
	rel = v_to_world(rel, rot);
	light->pos = add(pivot, rel);
}
