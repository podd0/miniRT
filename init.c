#include <rt.h>

t_img	*init_image(void *mlx, int win_w, int win_h)
{
	t_img *img;

	img = malloc(sizeof(t_img));
	img->img = mlx_new_image(mlx, win_w, win_h);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
		&img->endian);
	img->width = win_w;
    img->height = win_h;
	return (img);
}

// return a ctx, or exit cleanly on error
// t_ctx	init(char *filename)
// {
// 	t_ctx	ctx;

// 	ft_bzero(&ctx.control, sizeof(t_control));
// 	ctx.rounds = 0;
// 	ctx.win_w = WIN_W;
// 	ctx.win_h = WIN_H;
// 	ctx.img_vec = ft_calloc(ctx.win_w * ctx.win_h, sizeof(t_vec3));
// 	ctx.scene = parse(filename);
// 	ctx.mlx = mlx_init();
// 	ctx.mlx_win = mlx_new_window(ctx.mlx, ctx.win_w, ctx.win_h, "miniRT");
// 	ctx.img = init_image(ctx.mlx, ctx.win_w, ctx.win_h);
// 	if (!ctx.scene || !ctx.mlx || !ctx.mlx_win)
// 	{
// 		ft_putstr_fd("Error\n", 2);
// 		exit(1);
// 	}
// 	ctx.control.mlx = ctx.mlx;
// 	return (ctx);
// }

t_ctx init(char *filename)
{
    t_ctx ctx;

    ft_bzero(&ctx.control, sizeof(t_control));
    ctx.rounds = 0;
    ctx.win_w = WIN_W;
    ctx.win_h = WIN_H;
    ctx.img_vec = ft_calloc(ctx.win_w * ctx.win_h, sizeof(t_vec3));
    ctx.scene = parse(filename);
    ctx.mlx = mlx_init();
    ctx.mlx_win = mlx_new_window(ctx.mlx, ctx.win_w, ctx.win_h, "miniRT");

    ctx.img = init_image(ctx.mlx, ctx.win_w, ctx.win_h);
    if (!ctx.scene || !ctx.mlx || !ctx.mlx_win)
    {
        ft_putstr_fd("Error\n", 2);
        exit(1);
    }
    return (ctx);
}

