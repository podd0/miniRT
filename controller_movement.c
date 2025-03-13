/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_movement.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:13:52 by amema             #+#    #+#             */
/*   Updated: 2025/03/13 11:15:30 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	apply_movement(t_ctx *ctx)
{
	t_vec3	movement;
	t_light	*light;

	movement = norm(v_to_world(ctx->control.delta, ctx->scene->camera),
			MOVE_SPEED);
	if (ctx->control.selected_light != -1)
	{
		light = ctx->scene->lights->arr[ctx->control.selected_light];
		light->pos = add(movement, light->pos);
	}
	else if (ctx->selected)
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

void	move(t_ctx *ctx)
{
	if (vec_length(ctx->control.delta) != 0)
	{
		apply_movement(ctx);
		ctx->control.reset = 1;
	}
}

void	rotate(t_ctx *ctx)
{
	t_frame	rot;
	int		selected_light;

	if (!ctx->control.rotating)
		return ;
	selected_light = ctx->control.selected_light;
	rot = ctx->control.rotation;
	if (ctx->selected)
		ctx->selected->methods->rotate(ctx->selected->obj, rot);
	else if (selected_light != -1)
		rotate_light((t_light *)ctx->scene->lights->arr[selected_light], rot);
	else
		rotate_camera(&ctx->scene->camera, rot);
	ctx->control.reset = 1;
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
	move(ctx);
	rotate(ctx);
	if (ctx->control.reset)
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
	t_vec3		direction;
	t_vec3		p;
	t_shape		*sh;
	t_screen	screen;

	if (k != 1)
		return (0);
	screen.x = x;
	screen.y = y;
	screen.win_w = ctx->win_w;
	screen.win_h = ctx->win_h;
	direction = calc_direction(screen, ctx->scene->fov, ctx->scene->camera);
	sh = intersect_scene(&p, direction, ctx->scene,
			ctx->scene->camera.o);
	clear_selection(ctx);
	ctx->control.selected_light = -1;
	if (sh)
	{
		ctx->selection_color = sh->color;
		sh->color = (t_vec3){1, 0, 0};
		ctx->selected = sh;
		ctx->control.reset = 1;
	}
	return (0);
}

static void	toggle_light(t_ctx *ctx)
{
	t_control	*ctrl;

	ctrl = &ctx->control;
	ctrl->selected_light++;
	if (ctrl->selected_light >= ctx->scene->lights->size)
	{
		ctrl->selected_light = -1;
		printf("Light mode: no light selected\n");
	}
	else
		printf("Light mode: selected light #%d\n", ctrl->selected_light);
	ctrl->reset = 1;
	clear_selection(ctx);
}

static void	process_window_resize(int key, t_ctx *ctx)
{
	if (key == 65363 && ctx->control.shift)
		virtual_resize(ctx, ctx->win_w + 200, ctx->win_h);
	else if (key == 65364 && ctx->control.shift)
		virtual_resize(ctx, ctx->win_w, ctx->win_h + 200);
	else if (key == 65361 && ctx->control.shift)
	{
		ctx->win_w -= 200;
		if (ctx->win_w < 100)
			ctx->win_w = 100;
		virtual_resize(ctx, ctx->win_w, ctx->win_h);
	}
	else if (key == 65362 && ctx->control.shift)
	{
		ctx->win_h -= 200;
		if (ctx->win_h < 100)
			ctx->win_h = 100;
		virtual_resize(ctx, ctx->win_w, ctx->win_h);
	}
}

static void	process_object_scale(int key, t_ctx *ctx)
{
	if (key == 61)
	{
		if (ctx->selected->methods == &ctx->scene->methods[SPHERE])
			resize_sphere((t_sphere *)ctx->selected->obj, 1.0f);
		else if (ctx->selected->methods == &ctx->scene->methods[CYLINDER])
			resize_cylinder_diameter((t_cylinder *)ctx->selected->obj, 0.5f);
		reset_show(ctx);
	}
	else if (key == 45)
	{
		if (ctx->selected->methods == &ctx->scene->methods[SPHERE])
			resize_sphere((t_sphere *)ctx->selected->obj, -1.0f);
		else if (ctx->selected->methods == &ctx->scene->methods[CYLINDER])
			resize_cylinder_diameter((t_cylinder *)ctx->selected->obj, -0.5f);
		reset_show(ctx);
	}
}

static void	process_object_height(int key, t_ctx *ctx)
{
	if (key == 91)
	{
		if (ctx->selected->methods == &ctx->scene->methods[CYLINDER])
			resize_cylinder_height((t_cylinder *)ctx->selected->obj, -0.5f);
		reset_show(ctx);
	}
	else if (key == 93)
	{
		if (ctx->selected->methods == &ctx->scene->methods[CYLINDER])
			resize_cylinder_height((t_cylinder *)ctx->selected->obj, 0.5f);
		reset_show(ctx);
	}
}

static void	process_rotation_keys(int key, t_ctx *ctx)
{
	t_frame		*rot;
	float		angle;

	if (key != 'i' && key != 'k' && key != 'j'
		&& key != 'l' && key != 'u' && key != 'o')
		return ;
	ctx->control.rotating = 1;
	angle = 5.0f;
	rot = &ctx->control.rotation;
	if (key == 'i')
		*rot = rotx(angle);
	else if (key == 'k')
		*rot = rotx(-angle);
	else if (key == 'j')
		*rot = roty(angle);
	else if (key == 'l')
		*rot = roty(-angle);
	else if (key == 'u')
		*rot = rotz(angle);
	else
		*rot = rotz(-angle);
	reset_show(ctx);
}

static int	process_exit_and_toggle(int key, t_ctx *ctx)
{
	if (key == 65307)
	{
		mlx_loop_end(ctx->mlx);
		return (1);
	}
	if (key == 'm')
	{
		toggle_light(ctx);
		return (1);
	}
	return (0);
}

static void	process_clear_selection(int key, t_ctx *ctx)
{
	if (key == 65293)
	{
		clear_selection(ctx);
		ctx->control.selected_light = -1;
	}
}

static int	process_basic_keys(int key, t_ctx *ctx)
{
	if (process_exit_and_toggle(key, ctx))
		return (1);
	process_clear_selection(key, ctx);
	return (0);
}

static void	process_movement_keys(int key, t_ctx *ctx)
{
	t_control	*ctrl;

	ctrl = &ctx->control;
	process_window_resize(key, ctx);
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
	else if (key == 't')
	{
		ctrl->reset = 1;
		ctrl->path_tracing = !ctrl->path_tracing;
	}
}

static void	process_transform_keys(int key, t_ctx *ctx)
{
	if (ctx->selected)
	{
		if (key == 61 || key == 45)
			process_object_scale(key, ctx);
		else if (key == 91 || key == 93)
			process_object_height(key, ctx);
	}
	process_rotation_keys(key, ctx);
}

int	handle_key_down(int key, t_ctx *ctx)
{
	if (process_basic_keys(key, ctx))
		return (0);
	printf("press key (%d)\n", key);
	process_movement_keys(key, ctx);
	process_transform_keys(key, ctx);
	return (0);
}

int	handle_key_up(int key, t_control *ctrl)
{
	printf("press key (%d)\n", key);
	if (key == 65505 || key == 65506)
		ctrl->shift = max(0, ctrl->shift - 1);
	if (key == 'w')
		ctrl->delta.z -= 1;
	else if (key == 's')
		ctrl->delta.z -= -1;
	else if (key == 'a')
		ctrl->delta.x -= 1;
	else if (key == 'd')
		ctrl->delta.x -= -1;
	else if (key == ' ')
		ctrl->space = 0;
	else if (key == 'i' || key == 'k' || key == 'j'
		|| key == 'l' || key == 'u' || key == 'o')
		ctrl->rotating = 0;
	return (0);
}
