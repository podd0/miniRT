/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:55:23 by amema             #+#    #+#             */
/*   Updated: 2025/03/13 15:55:25 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	loop(t_ctx *ctx)
{
	preproc_ctrl(&ctx->control);
	move(ctx);
	rotate(ctx);
	if (ctx->control.reset)
		reset_show(ctx);
	update_show(ctx);
	return (0);
}

void	clear_selection(t_ctx *ctx)
{
	if (!ctx->selected)
		return ;
	ctx->selected->color = ctx->selection_color;
	ctx->selected = NULL;
	ctx->control.reset = 1;
}

int	handle_mouse(int k, int x, int y, t_ctx *ctx)
{
	t_vec3		direction;
	t_vec3		p;
	t_shape		*sh;
	t_screen	screen;

	if (k != 1)
		return (0);
	screen.x = x;
	screen.y = y;
	screen.win_w = ctx->win_w;
	screen.win_h = ctx->win_h;
	direction = calc_direction(screen, ctx->scene->fov, ctx->scene->camera);
	sh = intersect_scene(&p, direction, ctx->scene, ctx->scene->camera.o);
	clear_selection(ctx);
	ctx->control.selected_light = -1;
	if (sh)
	{
		ctx->selection_color = sh->color;
		sh->color = (t_vec3){1, 0, 0};
		ctx->selected = sh;
		ctx->control.reset = 1;
	}
	return (0);
}
