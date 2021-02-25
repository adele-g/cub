#include "cub3d.h"

void	key_right(t_all *all)
{
	if (all->var.map[(int)(all->var.pos_x + all->var.plane_x *
		all->var.move_speed)][(int)all->var.pos_y] == '0')
		all->var.pos_x += all->var.plane_x * all->var.move_speed;
	if (all->var.map[(int)all->var.pos_x][(int)(all->var.pos_y +
	all->var.plane_y * all->var.move_speed)] == '0')
		all->var.pos_y += all->var.plane_y * all->var.move_speed;
}

void	key_left(t_all *all)
{
	if (all->var.map[(int)(all->var.pos_x - all->var.plane_x *
	all->var.move_speed)][(int)all->var.pos_y] == '0')
		all->var.pos_x -= all->var.plane_x * all->var.move_speed;
	if (all->var.map[(int)all->var.pos_x][(int)(all->var.pos_y -
	all->var.plane_y * all->var.move_speed)] == '0')
		all->var.pos_y -= all->var.plane_y * all->var.move_speed;
}

int		move(int keycode, t_all *all)
{
	if (keycode == 13)
		key_go_forward(all);
	if (keycode == 1)
		key_go_backward(all);
	if (keycode == 2)
		key_right(all);
	if (keycode == 0)
		key_left(all);
	if (keycode == 53)
	{
		mlx_destroy_image(all->mlx.mlx, all->mlx.img);
		mlx_destroy_window(all->mlx.mlx, all->mlx.win);
		exit(0);
	}
	if (keycode == 124)
		key_right_rotation(all);
	if (keycode == 123)
		key_left_rot(all);
	draw(all);
	mlx_do_sync(all->mlx.mlx);
	return (1);
}

int		ft_close(t_all *all)
{
	mlx_destroy_image(all->mlx.mlx, all->mlx.img);
	mlx_destroy_window(all->mlx.mlx, all->mlx.win);
	exit(0);
}
