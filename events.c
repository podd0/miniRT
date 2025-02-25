/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:11:03 by amema             #+#    #+#             */
/*   Updated: 2025/02/25 13:26:51 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

int	handle_resize(XEvent *e, void *param)
{
	t_ctx	*ctx;
	int		new_w;
	int		new_h;

	ctx = (t_ctx *)param;
	if (e->type != ConfigureNotify)
		return (0);
	new_w = e->xconfigure.width;
	new_h = e->xconfigure.height;
	printf("Resize event: new_w = %d, new_h = %d\n", new_w, new_h);
	if (new_w == ctx->win_w && new_h == ctx->win_h)
		return (0);
	ctx->win_w = new_w;
	ctx->win_h = new_h;
	mlx_destroy_image(ctx->mlx, ctx->img->img);
	free(ctx->img);
	ctx->img = init_image(ctx->mlx, ctx->win_w, ctx->win_h);
	free(ctx->img_vec);
	ctx->img_vec = ft_calloc(ctx->win_w * ctx->win_h, sizeof(t_vec3));
	mlx_clear_window(ctx->mlx, ctx->mlx_win);
	reset_show(ctx);
	update_show(ctx);
	return (0);
}
