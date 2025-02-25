/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_resize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:37:06 by amema             #+#    #+#             */
/*   Updated: 2025/02/25 15:37:09 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	virtual_resize(t_ctx *ctx, int new_w, int new_h)
{
	ctx->win_w = new_w;
	ctx->win_h = new_h;
	mlx_destroy_image(ctx->mlx, ctx->img->img);
	free(ctx->img);
	ctx->img = init_image(ctx->mlx, ctx->win_w, ctx->win_h);
	free(ctx->img_vec);
	ctx->img_vec = ft_calloc(ctx->win_w * ctx->win_h, sizeof(t_vec3));
	if (!ctx->img_vec)
	{
		printf("Errore allocazione img_vec per %d elementi\n",
			ctx->win_w * ctx->win_h);
		exit(1);
	}
	mlx_destroy_window(ctx->mlx, ctx->mlx_win);
	ctx->mlx_win = mlx_new_window(ctx->mlx, new_w, new_h, "miniRT");
	mlx_hook(ctx->mlx_win, 2, 1L << 0, handle_key_down, ctx);
	mlx_hook(ctx->mlx_win, 3, 1L << 1, handle_key_up, &ctx->control);
	mlx_hook(ctx->mlx_win, 17, 1L << 17, mlx_loop_end, ctx->mlx);
	mlx_mouse_hook(ctx->mlx_win, handle_mouse, ctx);
	reset_show(ctx);
}
