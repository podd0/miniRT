/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 22:36:21 by apuddu            #+#    #+#             */
/*   Updated: 2024/11/02 22:36:30 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vec3	add(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

float	dot(const t_vec3 a, const t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	neg(const t_vec3 a)
{
	return ((t_vec3){-a.x, -a.y, -a.z});
}

t_vec3	sub(const t_vec3 a, const t_vec3 b)
{
	return (add(a, neg(b)));
}

t_vec3	scale(float f, const t_vec3 v)
{
	return ((t_vec3){v.x * f, v.y * f, v.z * f});
}
