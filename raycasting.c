#include "cub3d.h"

void	raycasting_n_draw(t_all *all, int i)
{
	int y;
	int j;

	y = 0;
	raycasting_init(all, i);
	calc_step(all, i);
	dda(all);
	raycast_calc(all);
	j = choose_texture(all);
	while (y < all->var.screen_height - 1)
	{
		if (y < all->var.draw_start)
			my_mlx_pixel_put(all, i, y, rgb(all->var.c_color));
		else if (y >= all->var.draw_start && y <= all->var.draw_end)
			draw_walls(all, j, i, y);
		else
			my_mlx_pixel_put(all, i, y, rgb(all->var.f_color));
		y++;
	}
	all->var.zbuffer[i] = all->var.perp_wall_dist;
}
