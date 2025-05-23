/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:28:06 by amema             #+#    #+#             */
/*   Updated: 2025/02/25 13:28:07 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_frame	f_to_world(t_frame f1, t_frame ref)
{
	t_frame	res;

	res.o = add(ref.o, f1.o);
	res.x = v_to_world(f1.x, ref);
	res.y = v_to_world(f1.y, ref);
	res.z = v_to_world(f1.z, ref);
	res.o = v_to_frame(res.o, ref);
	res.o = v_to_world(res.o, res);
	return (res);
}
