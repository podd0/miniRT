/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:41:50 by amema             #+#    #+#             */
/*   Updated: 2025/03/09 21:05:44 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <X11/Xutil.h>

static int	setup_hooks(t_ctx *ctx)
{
	mlx_hook(ctx->mlx_win, 2, 1L << 0, handle_key_down, ctx);
	mlx_hook(ctx->mlx_win, 3, 1L << 1, handle_key_up, &ctx->control);
	mlx_hook(ctx->mlx_win, 17, 1L << 17, mlx_loop_end, ctx->mlx);
	mlx_mouse_hook(ctx->mlx_win, handle_mouse, ctx);
	mlx_loop_hook(ctx->mlx, loop, ctx);
	return (0);
}

static void	cleanup(t_ctx *ctx)
{
	free_scene(ctx->scene);
	free(ctx->img_vec);
	mlx_destroy_window(ctx->mlx, ctx->mlx_win);
	mlx_destroy_image(ctx->mlx, ctx->img->img);
	free(ctx->img);
	mlx_destroy_display(ctx->mlx);
	free(ctx->mlx);
	free(ctx);
}

int	main(int argc, char **argv)
{
	t_ctx	*ctx;

	if (argc != 2)
	{
		printf("Usage : %s SCENE\n", argv[0]);
		return (0);
	}
	ctx = malloc(sizeof(t_ctx));
	if (!ctx)
	{
		perror("malloc");
		return (1);
	}
	*ctx = init(argv[1]);
	setup_hooks(ctx);
	mlx_loop(ctx->mlx);
	cleanup(ctx);
	return (0);
}

void	pvec(t_vec3 v)
{
	printf("(%f, %f, %f)", v.x, v.y, v.z);
}

void	pframe(t_frame f)
{
	printf("{");
	pvec(f.x);
	printf(",\n");
	pvec(f.y);
	printf(",\n");
	pvec(f.z);
	printf(",\n");
	pvec(f.o);
	printf("}\n");
}
