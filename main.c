#include <rt.h>
#include <X11/Xutil.h>  // Per XConfigureEvent



int main(int argc, char **argv)
{
    t_ctx *ctx;
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
    *ctx = init(argv[1]);  // inizializza il contesto

    mlx_hook(ctx->mlx_win, 2, 1L << 0, handle_key_down, ctx);
    mlx_hook(ctx->mlx_win, 3, 1L << 1, handle_key_up, &ctx->control);
    mlx_hook(ctx->mlx_win, 17, 1L << 17, mlx_loop_end, ctx->mlx);
    mlx_mouse_hook(ctx->mlx_win, handle_mouse, ctx);

    mlx_loop_hook(ctx->mlx, loop, ctx);
    mlx_loop(ctx->mlx);

    free_scene(ctx->scene);
    free(ctx->img_vec);
    mlx_destroy_window(ctx->mlx, ctx->mlx_win);
    mlx_destroy_image(ctx->mlx, ctx->img->img);
    free(ctx->img);
    mlx_destroy_display(ctx->mlx);
    free(ctx->mlx);
    free(ctx);
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

// int _main()
// {
// 	t_frame fr;
// 	fr = rotx(10);
// 	pframe(fr);
// 	printf("\n");
// 	while(1)
// 	{
// 		int x, y;
// 		scanf("%d %d", &x, &y);
// 		float fov = 1.0;
// 		t_vec3 rotated = rotx(y*fov).z;
// 		pvec(rotated);
// 		rotated = to_world(rotated, roty(x*fov));
// 		pvec(rotated);
// 		pvec(to_world(rotated, fr));
// 	}
// }