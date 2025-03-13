/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_keys_transform.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:52:35 by amema             #+#    #+#             */
/*   Updated: 2025/03/13 15:52:36 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	process_object_scale(int key, t_ctx *ctx)
{
	if (key == 61)
	{
		if (ctx->selected->methods == &ctx->scene->methods[SPHERE])
			resize_sphere((t_sphere *)ctx->selected->obj, 1.0f);
		else if (ctx->selected->methods == &ctx->scene->methods[CYLINDER])
			resize_cylinder_diameter((t_cylinder *)ctx->selected->obj, 0.5f);
		reset_show(ctx);
	}
	else if (key == 45)
	{
		if (ctx->selected->methods == &ctx->scene->methods[SPHERE])
			resize_sphere((t_sphere *)ctx->selected->obj, -1.0f);
		else if (ctx->selected->methods == &ctx->scene->methods[CYLINDER])
			resize_cylinder_diameter((t_cylinder *)ctx->selected->obj, -0.5f);
		reset_show(ctx);
	}
}

static void	process_object_height(int key, t_ctx *ctx)
{
	if (key == 91)
	{
		if (ctx->selected->methods == &ctx->scene->methods[CYLINDER])
			resize_cylinder_height((t_cylinder *)ctx->selected->obj, -0.5f);
		reset_show(ctx);
	}
	else if (key == 93)
	{
		if (ctx->selected->methods == &ctx->scene->methods[CYLINDER])
			resize_cylinder_height((t_cylinder *)ctx->selected->obj, 0.5f);
		reset_show(ctx);
	}
}

static void	process_rotation_keys(int key, t_ctx *ctx)
{
	t_frame		*rot;
	float		angle;

	if (key != 'i' && key != 'k' && key != 'j'
		&& key != 'l' && key != 'u' && key != 'o')
		return ;
	ctx->control.rotating = 1;
	angle = 5.0f;
	rot = &ctx->control.rotation;
	if (key == 'i')
		*rot = rotx(angle);
	else if (key == 'k')
		*rot = rotx(-angle);
	else if (key == 'j')
		*rot = roty(angle);
	else if (key == 'l')
		*rot = roty(-angle);
	else if (key == 'u')
		*rot = rotz(angle);
	else
		*rot = rotz(-angle);
	reset_show(ctx);
}

void	process_transform_keys(int key, t_ctx *ctx)
{
	if (ctx->selected)
	{
		if (key == 61 || key == 45)
			process_object_scale(key, ctx);
		else if (key == 91 || key == 93)
			process_object_height(key, ctx);
	}
	process_rotation_keys(key, ctx);
}
