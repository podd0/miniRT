/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:33:37 by apuddu            #+#    #+#             */
/*   Updated: 2025/02/13 23:14:54 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>




int main(int argc, char **argv)
{
	t_ctx	ctx;
	if (argc != 2)
	{
		printf("Usage : %s SCENE\n", argv[0]);
		return (0);
	}
	ctx = init(argv[1]);
	// trace(&ctx);
	mlx_hook(ctx.mlx_win, 2, 1L << 0, handle_key_down, &ctx.control);
	mlx_hook(ctx.mlx_win, 3, 1L << 1, handle_key_up, &ctx.control);
	mlx_hook(ctx.mlx_win, 17, 1L << 17, mlx_loop_end, ctx.mlx);
	mlx_loop_hook(ctx.mlx, loop, &ctx);
	mlx_loop(ctx.mlx);

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