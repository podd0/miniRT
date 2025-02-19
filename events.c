#include <rt.h>
#include <X11/Xlib.h>  // Per usare XGetWindowAttributes
#include <X11/Xutil.h>

int handle_resize(XEvent *e, void *param)
{
    t_ctx *ctx = (t_ctx *)param;
    if (e->type != ConfigureNotify)
        return (0);

    int new_w = e->xconfigure.width;
    int new_h = e->xconfigure.height;
    printf("Resize event: new_w = %d, new_h = %d\n", new_w, new_h);

    if (new_w == ctx->win_w && new_h == ctx->win_h)
        return (0);

    // Aggiorna dimensioni e ricalcola la scena...
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

// func verrà chiamata quando la finestra viene ridimensionata
// int handle_resize(void *param)
// {
//     t_ctx *ctx = (t_ctx *)param;
//     XWindowAttributes attr;
//     Display *dpy;

//     // Prova prima con il display contenuto in ctx->mlx
//     dpy = *((Display **)ctx->mlx);

//     printf("handle_resize: ctx->mlx = %p, ctx->mlx_win = %p\n", ctx->mlx, ctx->mlx_win);
    
//     if (!dpy)
//     {
//         printf("Display pointer ottenuto da ctx->mlx è NULL\n");
//         return (0);
//     }

//     // Prova a stampare il window id (come unsigned long)
//     printf("handle_resize: window id = %lu\n", (unsigned long)ctx->mlx_win);

//     // Prova la chiamata a XGetWindowAttributes
//     if (XGetWindowAttributes(dpy, (Window)ctx->mlx_win, &attr) == 0)
//     {
//         printf("XGetWindowAttributes ha fallito\n");
//         return (0);
//     }
    
//     int new_w = attr.width;
//     int new_h = attr.height;
//     printf("handle_resize: new_w = %d, new_h = %d\n", new_w, new_h);

//     if (new_w == ctx->win_w && new_h == ctx->win_h)
//         return (0);

//     ctx->win_w = new_w;
//     ctx->win_h = new_h;

//     mlx_destroy_image(ctx->mlx, ctx->img->img);
//     free(ctx->img);
//     ctx->img = init_image(ctx->mlx, ctx->win_w, ctx->win_h);

//     free(ctx->img_vec);
//     ctx->img_vec = ft_calloc(ctx->win_w * ctx->win_h, sizeof(t_vec3));

//     reset_show(ctx);
//     update_show(ctx);

//     return (0);
// }

