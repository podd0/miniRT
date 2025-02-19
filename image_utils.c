#include <rt.h>

unsigned int	col_from_vec(t_vec3 v)
{
	return (((int)v.x << 16) | ((int)v.y << 8) | ((int)v.z));
}

void	pixel_put(t_img *img, int x, int y, t_vec3 color)
{
	char	*dst;

	if (x >= img->width || y >= img->height || x < 0 || y < 0 )
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = col_from_vec(color);
}

void	pixel_put_centered(t_img *img, int x, int y, t_vec3 color)
{
	x += img->width / 2;
	y += img->height / 2;
	pixel_put(img, x, y, color);
}
