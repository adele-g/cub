#include "cub3d.h"

void	key_go_forward(t_all *all)
{
	if (all->var.map[(int)(all->var.pos_x + all->var.dir_x *
	all->var.move_speed)][(int)all->var.pos_y] == '0')
		all->var.pos_x += all->var.dir_x * all->var.move_speed;
	if (all->var.map[(int)all->var.pos_x][(int)(all->var.pos_y +
	all->var.dir_y * all->var.move_speed)] == '0')
		all->var.pos_y += all->var.dir_y * all->var.move_speed;
}

void	key_go_backward(t_all *all)
{
	if (all->var.map[(int)(all->var.pos_x - all->var.dir_x *
	all->var.move_speed)][(int)all->var.pos_y] == '0')
		all->var.pos_x -= all->var.dir_x * all->var.move_speed;
	if (all->var.map[(int)all->var.pos_x][(int)(all->var.pos_y -
	all->var.dir_y * all->var.move_speed)] == '0')
		all->var.pos_y -= all->var.dir_y * all->var.move_speed;
}

void	key_right_rotation(t_all *all)
{
	all->var.old_dir_x = all->var.dir_x;
	all->var.dir_x = all->var.dir_x * cos(-all->var.rot_speed) -
	all->var.dir_y * sin(-all->var.rot_speed);
	all->var.dir_y = all->var.old_dir_x * sin(-all->var.rot_speed) +
	all->var.dir_y * cos(-all->var.rot_speed);
	all->var.old_plane_x = all->var.plane_x;
	all->var.plane_x = all->var.plane_x * cos(-all->var.rot_speed) -
	all->var.plane_y * sin(-all->var.rot_speed);
	all->var.plane_y = all->var.old_plane_x * sin(-all->var.rot_speed) +
	all->var.plane_y * cos(-all->var.rot_speed);
}

void	key_left_rot(t_all *all)
{
	all->var.old_dir_x = all->var.dir_x;
	all->var.dir_x = all->var.dir_x * cos(all->var.rot_speed) -
	all->var.dir_y * sin(all->var.rot_speed);
	all->var.dir_y = all->var.old_dir_x * sin(all->var.rot_speed) +
	all->var.dir_y * cos(all->var.rot_speed);
	all->var.old_plane_x = all->var.plane_x;
	all->var.plane_x = all->var.plane_x * cos(all->var.rot_speed) -
	all->var.plane_y * sin(all->var.rot_speed);
	all->var.plane_y = all->var.old_plane_x * sin(all->var.rot_speed) +
	all->var.plane_y * cos(all->var.rot_speed);
}
