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
    printf("virtual_resize: Buffer allocato: %d elementi, indirizzo %p\n",
           ctx->win_w * ctx->win_h, ctx->img_vec);
    reset_show(ctx);
    update_show(ctx);
    printf("virtual_resize completato: new_w = %d, new_h = %d\n", ctx->win_w, ctx->win_h);
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
