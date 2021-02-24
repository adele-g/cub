#include "cub3d.h"

void	raycasting_init(t_all *all, int i)
{
	all->var.camera_x = 2 * i / (double)(all->var.screen_width) - 1;
	all->var.ray_dir_x = all->var.dir_x + all->var.plane_x * all->var.camera_x;
	all->var.ray_dir_y = all->var.dir_y + all->var.plane_y * all->var.camera_x;
	all->var.side_dist_x = fabs(1 / all->var.ray_dir_x);
	all->var.side_dist_y = fabs(1 / all->var.ray_dir_y);
	all->var.hit = 0;
	all->var.delta_dist_x = fabs(1 / all->var.ray_dir_x);
	all->var.delta_dist_y = fabs(1 / all->var.ray_dir_y);
	all->var.map_x = (int)all->var.pos_x;
	all->var.map_y = (int)all->var.pos_y;
}

void	calc_step(t_all *all, int i)
{
	if (all->var.ray_dir_x < 0)
	{
		all->var.step_x = -1;
		all->var.side_dist_x = (all->var.pos_x - all->var.map_x) *
		all->var.delta_dist_x;
	}
	else
	{
		all->var.step_x = 1;
		all->var.side_dist_x = (all->var.map_x + 1.0 - all->var.pos_x) *
		all->var.delta_dist_x;
	}
	if (all->var.ray_dir_y < 0)
	{
		all->var.step_y = -1;
		all->var.side_dist_y = (all->var.pos_y - all->var.map_y) *
		all->var.delta_dist_y;
	}
	else
	{
		all->var.step_y = 1;
		all->var.side_dist_y = (all->var.map_y + 1.0 - all->var.pos_y) *
		all->var.delta_dist_y;
	}
}

void	dda(t_all *all)
{
	while (all->var.hit == 0)
	{
		if (all->var.side_dist_x < all->var.side_dist_y)
		{
			all->var.side_dist_x += all->var.delta_dist_x;
			all->var.map_x += all->var.step_x;
			all->var.side = 0;
		}
		else
		{
			all->var.side_dist_y += all->var.delta_dist_y;
			all->var.map_y += all->var.step_y;
			all->var.side = 1;
		}
		if (all->var.map[all->var.map_x][all->var.map_y] == '1')
			all->var.hit = 1;
	}
	if (all->var.side == 0)
		all->var.perp_wall_dist = (all->var.map_x - all->var.pos_x +
		(1 - all->var.step_x) / 2) / all->var.ray_dir_x;
	else
		all->var.perp_wall_dist = (all->var.map_y - all->var.pos_y +
		(1 - all->var.step_y) / 2) / all->var.ray_dir_y;
}

void	raycast_calc(t_all *all)
{
	all->var.line_height = (int)(all->var.screen_height /
	all->var.perp_wall_dist);
	all->var.draw_start = -all->var.line_height / 2 + all->var.screen_height /
	2;
	all->var.draw_end = all->var.line_height / 2 + all->var.screen_height / 2;
	if (all->var.draw_end >= all->var.screen_height)
		all->var.draw_end = all->var.screen_height - 1;
	if (all->var.side == 0)
		all->var.wall_x = all->var.pos_y + all->var.perp_wall_dist *
		all->var.ray_dir_y;
	else
		all->var.wall_x = all->var.pos_x + all->var.perp_wall_dist *
		all->var.ray_dir_x;
	all->var.wall_x -= floor(all->var.wall_x);
}

int		choose_texture(t_all *all)
{
	int j;

	j = 0;
	if (all->var.side == 0 && all->var.map_x > all->var.pos_x)
		j = 0;
	if (all->var.side == 0 && all->var.map_x < all->var.pos_x)
		j = 1;
	if (all->var.side == 1 && all->var.map_y > all->var.pos_y)
		j = 2;
	if (all->var.side == 1 && all->var.map_y < all->var.pos_y)
		j = 3;
	all->var.tex_x = (int)(all->var.wall_x * (double)(all->text.width[j]));
	all->var.step = 1.0 * (all->text.height[j] / (int)all->var.line_height);
	return (j);
}
