#include <rt.h>

void	apply_movement(t_ctx *ctx)
{
	ctx->scene->camera.o = add(norm(v_to_frame(ctx->control.delta, ctx->scene->camera), MOVE_SPEED), ctx->scene->camera.o);
	printf("moving by "); pvec(ctx->control.delta); printf("\n");
}

void	reset_show(t_ctx *ctx)
{
	ctx->rounds = 0;
	ctx->control.reset = 0;
	ft_bzero(ctx->img_vec, WIN_H * WIN_W * sizeof(t_vec3));	
}

int move(t_ctx* ctx)
{
	if (vec_length(ctx->control.delta) != 0)
		apply_movement(ctx);
	else 
		return (0);
	
	return (1);
}

void	preproc_ctrl(t_control *ctrl)
{
	ctrl->delta.y = - (ctrl->space != 0);
	if (ctrl->shift)
		ctrl->delta.y *= -1;

}

int	loop(t_ctx *ctx)
{
	preproc_ctrl(&ctx->control);
	if (move(ctx) || ctx->control.reset)
		reset_show(ctx);
	update_show(ctx);
	return (0);
}


int	handle_key_down(int key, t_control *ctrl)
{
	printf("press key (%d)\n", key);
	if (key == 65505 || key == 65506)
		ctrl->shift++;
	else if (key == 'w')
		ctrl->delta.z += 1;
	else if (key == 's')
		ctrl->delta.z += -1;
	else if (key == 'a')
		ctrl->delta.x += 1;
	else if (key == 'd')
		ctrl->delta.x += -1;
	else if (key == ' ')
		ctrl->space = 1;
	else if (key == 65307)
		mlx_loop_end(ctrl->mlx);
	else if (key == 't')
	{
		ctrl->reset = 1;
		ctrl->path_tracing = !ctrl->path_tracing;
	}
	return (0);
}

int	handle_key_up(int key, t_control *ctrl)
{
	printf("press key (%d)\n", key);
	if (key == 65505 || key == 65506)
	{
		ctrl->shift = max(0, ctrl->shift - 1);
	}
	if (key == 'w')
		ctrl->delta.z -= 1;
	else if (key == 's')
		ctrl->delta.z -= -1;
	else if (key == 'a')
		ctrl->delta.x -= 1;
	if (key == 'd')
		ctrl->delta.x -= -1;
	else if (key == ' ')
		ctrl->space = 0;

	return (0);
}