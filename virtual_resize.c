
#include <rt.h>
void virtual_resize(t_ctx *ctx, int new_w, int new_h)
{
    ctx->win_w = new_w;
    ctx->win_h = new_h;
    mlx_destroy_image(ctx->mlx, ctx->img->img);
    free(ctx->img);
    ctx->img = init_image(ctx->mlx, ctx->win_w, ctx->win_h);
    free(ctx->img_vec);
    ctx->img_vec = ft_calloc(ctx->win_w * ctx->win_h, sizeof(t_vec3));
    if (!ctx->img_vec) {
        printf("Errore allocazione img_vec per %d elementi\n", ctx->win_w * ctx->win_h);
        exit(1);
    }
    mlx_destroy_window(ctx->mlx, ctx->mlx_win);
    ctx->mlx_win = mlx_new_window(ctx->mlx, new_w, new_h, "miniRT");
    mlx_hook(ctx->mlx_win, 2, 1L << 0, handle_key_down, &ctx->control);
    mlx_hook(ctx->mlx_win, 3, 1L << 1, handle_key_up, &ctx->control);
    mlx_hook(ctx->mlx_win, 17, 1L << 17, mlx_loop_end, ctx->mlx);
    mlx_mouse_hook(ctx->mlx_win, show_mouse, ctx);

    printf("virtual_resize: Buffer allocato: %d elementi, indirizzo %p\n",
           ctx->win_w * ctx->win_h, ctx->img_vec);
    reset_show(ctx);
}

// void virtual_resize(t_ctx *ctx, int new_w, int new_h)
// {
//     // Aggiorna le dimensioni nel contesto
//     ctx->win_w = new_w;
//     ctx->win_h = new_h;

//     // Distruggi l'immagine corrente e rialloca
//     mlx_destroy_image(ctx->mlx, ctx->img->img);
//     free(ctx->img);
//     ctx->img = init_image(ctx->mlx, ctx->win_w, ctx->win_h);

//     // Rialloca il buffer dell'immagine
//     free(ctx->img_vec);
//     ctx->img_vec = ft_calloc(ctx->win_w * ctx->win_h, sizeof(t_vec3));
//     if (!ctx->img_vec)
//     {
//         printf("Errore: allocazione di img_vec fallita per %d * %d = %d elementi\n", ctx->win_w, ctx->win_h, ctx->win_w * ctx->win_h);
//         exit(1);
//     }
//     else
//     {
//         printf("Buffer allocato: %d elementi\n", ctx->win_w * ctx->win_h);
//     }

//     // Ripristina e aggiorna la scena
//     reset_show(ctx);
//     update_show(ctx);

//     printf("Virtual resize: new_w = %d, new_h = %d\n", ctx->win_w, ctx->win_h);
// }
