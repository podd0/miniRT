/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:41:27 by amema             #+#    #+#             */
/*   Updated: 2025/03/09 20:15:17 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	apply_movement(t_ctx *ctx)
{
	t_vec3	movement;

	movement = norm(v_to_frame(ctx->control.delta, ctx->scene->camera),
			MOVE_SPEED);
	if (ctx->selected)
		ctx->selected->methods->move(ctx->selected->obj, movement);
	else
		ctx->scene->camera.o = add(movement, ctx->scene->camera.o);
}

void	reset_show(t_ctx *ctx)
{
	ctx->rounds = 0;
	ctx->control.reset = 0;
	ft_bzero(ctx->img_vec, ctx->win_w * ctx->win_h * sizeof(t_vec3));
}

int	move(t_ctx *ctx)
{
	if (vec_length(ctx->control.delta) != 0)
		apply_movement(ctx);
	else
		return (0);
	return (1);
}

void	preproc_ctrl(t_control *ctrl)
{
	ctrl->delta.y = -(ctrl->space != 0);
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

void	clear_selection(t_ctx *ctx)
{
	if (!ctx->selected)
		return ;
	ctx->selected->color = ctx->selection_color;
	ctx->selected = NULL;
	ctx->control.reset = 1;
}

int	handle_mouse(int k, int x, int y, t_ctx *ctx)
{
	t_vec3	direction;
	t_vec3	p;
	t_shape	*sh;
    t_screen screen;

	if (k != 1)
		return (0);
	screen.x = x;
    screen.y = y;
    screen.win_w = ctx->win_w;
    screen.win_h = ctx->win_h;
    direction = calc_direction(screen, ctx->scene->fov, ctx->scene->camera);
	sh = intersect_scene(&p, direction, ctx->scene, ctx->scene->camera.o);
	clear_selection(ctx);
	if (sh)
	{
		ctx->selection_color = sh->color;
		sh->color = (t_vec3){1, 0, 0};
		ctx->selected = sh;
		ctx->control.reset = 1;
	}
	return (0);
}

int	handle_key_down(int key, t_ctx *ctx)
{
	t_control	*ctrl;

	ctrl = &ctx->control;
	if (key == 65293)
	{
		clear_selection(ctx);
	}
	if (key == 65363 && ctrl->shift)
	{
		virtual_resize(ctx, ctx->win_w + 200, ctx->win_h);
		return (0);
	}
	if (key == 65364 && ctrl->shift)
	{
		virtual_resize(ctx, ctx->win_w, ctx->win_h + 200);
		return (0);
	}
	if (key == 65361 && ctrl->shift)
	{
		ctx->win_w -= 200;
		if (ctx->win_w < 100)
			ctx->win_w = 100;
		virtual_resize(ctx, ctx->win_w, ctx->win_h);
	}
	if (key == 65362 && ctrl->shift)
	{
		ctx->win_h -= 200;
		if (ctx->win_h < 100)
			ctx->win_h = 100;
		virtual_resize(ctx, ctx->win_w, ctx->win_h);
		return (0);
	}
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
		mlx_loop_end(ctx->mlx);
	else if (key == 't')
	{
		ctrl->reset = 1;
		ctrl->path_tracing = !ctrl->path_tracing;
	}
	
	// transform selected object
	if (ctx->selected)
    {
        if (key == 61) // '+'
        {
            if (ctx->selected->methods == &ctx->scene->methods[SPHERE])
                resize_sphere((t_sphere *)ctx->selected->obj, 1.0f);
            else if (ctx->selected->methods == &ctx->scene->methods[CYLINDER])
                resize_cylinder_diameter((t_cylinder *)ctx->selected->obj, 0.5f);
			reset_show(ctx);
        }
        else if (key == 45) // '-'
        {
            if (ctx->selected->methods == &ctx->scene->methods[SPHERE])
                resize_sphere((t_sphere *)ctx->selected->obj, -1.0f);
            else if (ctx->selected->methods == &ctx->scene->methods[CYLINDER])
                resize_cylinder_diameter((t_cylinder *)ctx->selected->obj, -0.5f);
			reset_show(ctx);
        }
        else if (key == 91) // '[' per - h cilindro
        {
            if (ctx->selected->methods == &ctx->scene->methods[CYLINDER])
                resize_cylinder_height((t_cylinder *)ctx->selected->obj, -0.5f);
			reset_show(ctx);
        }
        else if (key == 93) // ']' per: + h cilindro
        {
            if (ctx->selected->methods == &ctx->scene->methods[CYLINDER])
                resize_cylinder_height((t_cylinder *)ctx->selected->obj, 0.5f);
			reset_show(ctx);
		}
    }
	    // Comandi di rotazione: I/K per rotazione attorno all'asse X,
    // J/L per Y, U/O per Z.
    else if (key == 'i' || key == 'k' || key == 'j' ||
        key == 'l' || key == 'u' || key == 'o')
    {
		printf("Rotazione: tasto premuto = %c\n", key);
        t_frame rot;
        float angle = 5.0f; // angolo in gradi per ogni pressione
        if (key == 'i')
            rot = rotx(angle);
        else if (key == 'k')
            rot = rotx(-angle);
        else if (key == 'j')
            rot = roty(angle);
        else if (key == 'l')
            rot = roty(-angle);
        else if (key == 'u')
            rot = rotz(angle);
        else // (key == 'o')
            rot = rotz(-angle);
        if (ctx->selected)
        {
            if (ctx->selected->methods == &ctx->scene->methods[PLANE])
                rotate_plane((t_plane *)ctx->selected->obj, rot);
            else if (ctx->selected->methods == &ctx->scene->methods[CYLINDER])
                rotate_cylinder((t_cylinder *)ctx->selected->obj, rot);
        }
        else
            rotate_camera(&ctx->scene->camera, rot);
        reset_show(ctx);
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
