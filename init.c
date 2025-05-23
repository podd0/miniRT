/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:29:15 by amema             #+#    #+#             */
/*   Updated: 2025/03/13 18:42:25 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_img	*init_image(void *mlx, int win_w, int win_h)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(mlx, win_w, win_h);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	img->width = win_w;
	img->height = win_h;
	return (img);
}

t_ctx	init(char *filename)
{
	t_ctx	ctx;

	ft_bzero(&ctx, sizeof(t_ctx));
	ctx.control.selected_light = -1;
	ctx.rounds = 0;
	ctx.win_w = WIN_W;
	ctx.win_h = WIN_H;
	ctx.scene = parse(filename);
	ctx.mlx = mlx_init();
	ctx.mlx_win = mlx_new_window(ctx.mlx, ctx.win_w, ctx.win_h, "miniRT");
	ctx.img = init_image(ctx.mlx, ctx.win_w, ctx.win_h);
	if (!ctx.scene || !ctx.mlx || !ctx.mlx_win)
	{
		free(ctx.scene);
		mlx_destroy_image(ctx.mlx, ctx.img->img);
		mlx_destroy_window(ctx.mlx, ctx.mlx_win);
		mlx_destroy_display(ctx.mlx);
		free(ctx.img);
		free(ctx.mlx);
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	ctx.img_vec = ft_calloc(ctx.win_w * ctx.win_h, sizeof(t_vec3));
	return (ctx);
}
