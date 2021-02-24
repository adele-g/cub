#include "cub3d.h"

void			draw_walls(t_all *all, int j, int i, int y)
{
	all->text.coef = (float)all->var.line_height /
			(float)all->text.height[j];
	all->var.tex_y = (float)(y - all->var.draw_start);
	all->var.tex_y = all->var.tex_y / all->text.coef;
	if (all->var.tex_y > all->text.height[j])
		all->var.tex_y = all->text.height[j] - 1;
	all->var.dst = all->mlx.addr + (y * all->mlx.line_length + i *
			(all->mlx.bits_per_pixel / 8));
	all->var.src = all->text.addr[j] + ((int)all->var.tex_y *
										all->text.line_length[j] +
										all->var.tex_x *
										(all->text.bits_per_pixel[j] / 8));
	*(unsigned int *)all->var.dst = *(unsigned int *)all->var.src;
}

void			my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char	*dst;

	dst = all->mlx.addr + (y * all->mlx.line_length + x *
			(all->mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int	text_pix_color(t_all *all, int x, int y)
{
	char			*addr;
	unsigned int	color;

	addr = (all->text.addr[4] + (y * all->text.line_length[4] + x *
			(all->text.bits_per_pixel[4] / 8)));
	color = *(unsigned int*)addr;
	return (color);
}

int				rgb(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}
