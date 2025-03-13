/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_keys_basic.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:54:26 by amema             #+#    #+#             */
/*   Updated: 2025/03/13 16:27:38 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern void	process_movement_keys(int key, t_ctx *ctx);
extern void	process_transform_keys(int key, t_ctx *ctx);

static void	toggle_light(t_ctx *ctx)
{
	t_control	*ctrl;

	ctrl = &ctx->control;
	ctrl->selected_light++;
	if (ctrl->selected_light >= ctx->scene->lights->size)
	{
		ctrl->selected_light = -1;
		printf("Light mode: no light selected\n");
	}
	else
		printf("Light mode: selected light #%d\n", ctrl->selected_light);
	ctrl->reset = 1;
	clear_selection(ctx);
}

static int	process_exit_and_toggle(int key, t_ctx *ctx)
{
	if (key == 65307)
	{
		mlx_loop_end(ctx->mlx);
		return (1);
	}
	if (key == 'm')
	{
		toggle_light(ctx);
		return (1);
	}
	return (0);
}

static void	process_clear_selection(int key, t_ctx *ctx)
{
	if (key == 65293)
	{
		clear_selection(ctx);
		ctx->control.selected_light = -1;
	}
}

static int	process_basic_keys(int key, t_ctx *ctx)
{
	if (process_exit_and_toggle(key, ctx))
		return (1);
	process_clear_selection(key, ctx);
	return (0);
}

int	handle_key_down(int key, t_ctx *ctx)
{
	if (process_basic_keys(key, ctx))
		return (0);
	printf("press key (%d)\n", key);
	process_movement_keys(key, ctx);
	process_transform_keys(key, ctx);
	return (0);
}
