/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_keys_move.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:53:20 by amema             #+#    #+#             */
/*   Updated: 2025/03/13 15:53:22 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	process_window_resize(int key, t_ctx *ctx)
{
	if (key == 65363 && ctx->control.shift)
		virtual_resize(ctx, ctx->win_w + 200, ctx->win_h);
	else if (key == 65364 && ctx->control.shift)
		virtual_resize(ctx, ctx->win_w, ctx->win_h + 200);
	else if (key == 65361 && ctx->control.shift)
	{
		ctx->win_w -= 200;
		if (ctx->win_w < 100)
			ctx->win_w = 100;
		virtual_resize(ctx, ctx->win_w, ctx->win_h);
	}
	else if (key == 65362 && ctx->control.shift)
	{
		ctx->win_h -= 200;
		if (ctx->win_h < 100)
			ctx->win_h = 100;
		virtual_resize(ctx, ctx->win_w, ctx->win_h);
	}
}

void	process_movement_keys(int key, t_ctx *ctx)
{
	t_control	*ctrl;

	ctrl = &ctx->control;
	process_window_resize(key, ctx);
	if (key == 65505 || key == 65506)
		ctrl->shift++;
	else if (key == 'w')
		ctrl->delta.z += 1;
	else if (key == 's')
		ctrl->delta.z += -1;
	else if (key == 'a')
		ctrl->delta.x += 1;
	else if (key == 'd')
		ctrl->delta.x += -1;
	else if (key == ' ')
		ctrl->space = 1;
	else if (key == 't')
	{
		ctrl->reset = 1;
		ctrl->path_tracing = !ctrl->path_tracing;
	}
}

int	handle_key_up(int key, t_control *ctrl)
{
	printf("press key (%d)\n", key);
	if (key == 65505 || key == 65506)
		ctrl->shift = max(0, ctrl->shift - 1);
	if (key == 'w')
		ctrl->delta.z -= 1;
	else if (key == 's')
		ctrl->delta.z -= -1;
	else if (key == 'a')
		ctrl->delta.x -= 1;
	else if (key == 'd')
		ctrl->delta.x -= -1;
	else if (key == ' ')
		ctrl->space = 0;
	else if (key == 'i' || key == 'k' || key == 'j'
		|| key == 'l' || key == 'u' || key == 'o')
		ctrl->rotating = 0;
	return (0);
}
