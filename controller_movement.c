/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_movement.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:56:04 by amema             #+#    #+#             */
/*   Updated: 2025/03/13 16:28:32 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	apply_movement(t_ctx *ctx)
{
	t_vec3	movement;
	t_light	*light;

	movement = norm(v_to_world(ctx->control.delta, ctx->scene->camera),
			MOVE_SPEED);
	if (ctx->control.selected_light != -1)
	{
		light = ctx->scene->lights->arr[ctx->control.selected_light];
		light->pos = add(movement, light->pos);
	}
	else if (ctx->selected)
		ctx->selected->methods->move(ctx->selected->obj, movement);
	else
		ctx->scene->camera.o = add(movement, ctx->scene->camera.o);
}

void	reset_show(t_ctx *ctx)
{
	ctx->rounds = 0;
	ctx->control.reset = 0;
	ft_bzero(ctx->img_vec, ctx->win_w * ctx->win_h * sizeof(t_vec3));
}

void	move(t_ctx *ctx)
{
	if (vec_length(ctx->control.delta) != 0)
	{
		apply_movement(ctx);
		ctx->control.reset = 1;
	}
}

void	rotate(t_ctx *ctx)
{
	t_frame	rot;
	int		selected_light;

	if (!ctx->control.rotating)
		return ;
	selected_light = ctx->control.selected_light;
	rot = ctx->control.rotation;
	if (ctx->selected)
		ctx->selected->methods->rotate(ctx->selected->obj, rot);
	else if (selected_light != -1)
		rotate_light((t_light *)ctx->scene->lights->arr[selected_light], rot);
	else
		rotate_camera(&ctx->scene->camera, rot);
	ctx->control.reset = 1;
}

void	preproc_ctrl(t_control *ctrl)
{
	ctrl->delta.y = -(ctrl->space != 0);
	if (ctrl->shift)
		ctrl->delta.y *= -1;
}
