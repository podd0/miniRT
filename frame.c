/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:29:25 by apuddu            #+#    #+#             */
/*   Updated: 2024/11/02 22:39:57 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vec3	to_frame(t_vec3 p, t_frame fr)
{
	t_vec3	res;

	res = sub(p, fr.o);
	res = (t_vec3){dot(res, fr.x), dot(res, fr.y), dot(res, fr.z)};
	return (res);
}

t_vec3	v_to_frame(t_vec3 p, t_frame fr)
{
	t_vec3	res;

	res = (t_vec3){dot(p, fr.x), dot(p, fr.y), dot(p, fr.z)};
	return (res);
}

t_frame	f_to_frame(t_frame f1, t_frame ref)
{
	t_frame	res;

	res.o = to_frame(f1.o, ref);
	res.x = v_to_frame(f1.x, ref);
	res.y = v_to_frame(f1.y, ref);
	res.z = v_to_frame(f1.z, ref);
	return (res);
}

t_vec3	to_world(t_vec3 p, t_frame fr)
{
	t_vec3	res;

	res = add(p, fr.o);
	res = add(scale(p.x, fr.x), scale(p.y, fr.y));
	return (add(res, scale(p.z, fr.z)));
}

t_vec3	v_to_world(t_vec3 p, t_frame fr)
{
	t_vec3	res;

	res = add(scale(p.x, fr.x), scale(p.y, fr.y));
	return (add(res, scale(p.z, fr.z)));
}
