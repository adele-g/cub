#include "cub3d.h"
#include "math.h"
#include <string.h>

void            my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char    *dst;

	dst = all->mlx.addr + (y * all->mlx.line_length + x * (all->mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int	texpixcolor(t_texture *img, int x, int y)
{
	char			*addr;
	unsigned int	color;

	addr = (img->addr[0] + (y * img->line_length[0] + x * (img->bits_per_pixel[0] / 8)));
	color = *(unsigned int*)addr;
	return (color);
}

void 	draw(t_all *all)
{
	int i = 0;
	while (i < all->var.screen_width)
	{

		all->var.camera_x = 2 * i / (double)(all->var.screen_width) - 1;
		all->var.ray_dir_x = all->var.dir_x + all->var.plane_x * all->var.camera_x;
		all->var.ray_dir_y = all->var.dir_y + all->var.plane_y * all->var.camera_x;
		all->var.side_dist_x = fabs(1 / all->var.ray_dir_x);
		all->var.side_dist_y = fabs(1 / all->var.ray_dir_y);
		all->var.hit = 0;
		all->var.delta_dist_x = (all->var.ray_dir_y == 0) ? 0 : ((all->var.ray_dir_x == 0) ? 1 : fabs(1 / all->var.ray_dir_x));
		all->var.delta_dist_y = (all->var.ray_dir_x == 0) ? 0 : ((all->var.ray_dir_y == 0) ? 1 : fabs(1 / all->var.ray_dir_y));
		all->var.map_x = (int)all->var.pos_x;
		all->var.map_y = (int)all->var.pos_y;

		if (all->var.ray_dir_x < 0)
		{
			all->var.step_x = -1;
			all->var.side_dist_x = (all->var.pos_x - all->var.map_x) * all->var.delta_dist_x;
		}
		else
		{
			all->var.step_x = 1;
			all->var.side_dist_x = (all->var.map_x + 1.0 - all->var.pos_x) * all->var.delta_dist_x;
		}
		if (all->var.ray_dir_y < 0)
		{
			all->var.step_y = -1;
			all->var.side_dist_y = (all->var.pos_y - all->var.map_y) * all->var.delta_dist_y;
		}
		else
		{
			all->var.step_y = 1;
			all->var.side_dist_y = (all->var.map_y + 1.0 - all->var.pos_y) * all->var.delta_dist_y;
		}

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
			if (all->var.map[all->var.map_x][all->var.map_y] > 0)
				all->var.hit = 1;
		}


		if (all->var.side == 0)
			all->var.perp_wall_dist = (all->var.map_x - all->var.pos_x + (1 - all->var.step_x) / 2) / all->var.ray_dir_x;
		else
			all->var.perp_wall_dist = (all->var.map_y - all->var.pos_y + (1 - all->var.step_y) / 2) / all->var.ray_dir_y;

		all->var.line_height = (int)(all->var.screen_height / all->var.perp_wall_dist);
		all->var.draw_start = -all->var.line_height / 2 + all->var.screen_height / 2;
//		if (all->var.draw_start < 0)
//			all->var.draw_start = 0;

		all->var.draw_end = all->var.line_height / 2 + all->var.screen_height / 2;
		if (all->var.draw_end >= all->var.screen_height)
			all->var.draw_end = all->var.screen_height - 1;


		all->var.tex_num = all->var.map[all->var.map_y][all->var.map_x] - 1;

		if (all->var.side == 0)
			all->var.wall_x = all->var.pos_y + all->var.perp_wall_dist * all->var.ray_dir_y;
		else
			all->var.wall_x = all->var.pos_x + all->var.perp_wall_dist * all->var.ray_dir_x;

		all->var.wall_x -= floor(all->var.wall_x);




		int y = 0;
		int j = 0;
		if (all->var.side == 0 && all->var.map_x > all->var.pos_x)
			j = 0;
		if (all->var.side == 0 && all->var.map_x < all->var.pos_x)
			j = 1;
		if (all->var.side == 1 && all->var.map_y > all->var.pos_y)
			j = 2;
		if (all->var.side == 1 && all->var.map_y < all->var.pos_y)
			j = 3;

//		if (all->var.side == 0 && all->var.ray_dir_x > 0)
//			all->var.tex_x = (int)all->text.width[j] - all->var.tex_x - 1;
//		if (all->var.side == 1 && all->var.ray_dir_y < 0)
//			all->var.tex_x = (int)all->text.width[j] - all->var.tex_x - 1;

		all->var.tex_x = (int)(all->var.wall_x * (double)(all->text.width[j]));

		all->var.step = 1.0 * (all->text.height[j] / (int)all->var.line_height);


		all->var.tex_pos = (all->var.draw_start - all->var.screen_height / 2 + all->text.line_length[j] / 2) * all->var.step;
//		printf("j = %d side = %d dir x = %f dir y = %f pos x = %f pos y = %f\n", j, all->var.side, all->var.dir_x, all->var.dir_y, all->var.pos_x, all->var.pos_y);
 		while (y < all->var.screen_height - 1)
		{

			if (y < all->var.draw_start)
			{
				my_mlx_pixel_put(all, i, y,0x000823492);
			}
			else if (y >= all->var.draw_start && y <= all->var.draw_end)
			{
				all->text.coef = (float)all->var.line_height/(float)all->text.height[j];
				all->var.tex_y = (float)(y - all->var.draw_start);
				all->var.tex_y = all->var.tex_y / all->text.coef;
				if (all->var.tex_y > all->text.height[j])
				{
					all->var.tex_y = all->text.height[j] - 1;
				}

				all->var.dst = all->mlx.addr + (y * all->mlx.line_length + i * (all->mlx.bits_per_pixel / 8));
				all->var.src = all->text.addr[j] + ((int)all->var.tex_y * all->text.line_length[j] + all->var.tex_x * (all->text.bits_per_pixel[j] / 8));
				*(unsigned int*)all->var.dst = *(unsigned int*)all->var.src;
			}
			else
				my_mlx_pixel_put(all, i, y, 0x0093874);
			y++;
		}
    	i++;
	}
	mlx_put_image_to_window(all->mlx.mlx, all->mlx.win, all->mlx.img, 0, 0);
}

int move(int keycode, t_all *all)
{
	if (keycode == 13)
	{
		if (all->var.map[(int) (all->var.pos_x + all->var.dir_x *
												 all->var.move_speed)][(int) all->var.pos_y] ==
			0)
			all->var.pos_x += all->var.dir_x * all->var.move_speed;
		if (all->var.map[(int) all->var.pos_x][(int) (all->var.pos_y +
													  all->var.dir_y *
													  all->var.move_speed)] ==
			0)
			all->var.pos_y += all->var.dir_y * all->var.move_speed;
	}
	if (keycode == 1)
	{
		if (all->var.map[(int) (all->var.pos_x - all->var.dir_x *
												 all->var.move_speed)][(int) all->var.pos_y] ==
			0)
			all->var.pos_x -= all->var.dir_x * all->var.move_speed;
		if (all->var.map[(int) all->var.pos_x][(int) (all->var.pos_y -
													  all->var.dir_y *
													  all->var.move_speed)] ==
			0)
			all->var.pos_y -= all->var.dir_y * all->var.move_speed;
	}
	if (keycode == 2)
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
	if (keycode == 0)
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
	if (keycode == 53)
	{
		exit(0);
	}
	if (keycode == 124)
	{
		if (all->var.map[(int) (all->var.pos_x + all->var.plane_x *
												 all->var.move_speed)][(int) all->var.pos_y] ==
			0)
			all->var.pos_x += all->var.plane_x * all->var.move_speed;
		if (all->var.map[(int) all->var.pos_x][(int) (all->var.pos_y +
													  all->var.plane_y *
													  all->var.move_speed)] ==
			0)
			all->var.pos_y += all->var.plane_y * all->var.move_speed;
	}
	if (keycode == 123)
	{
		if (all->var.map[(int) (all->var.pos_x - all->var.plane_x *
												 all->var.move_speed)][(int) all->var.pos_y] ==
			0)
			all->var.pos_x -= all->var.plane_x * all->var.move_speed;
		if (all->var.map[(int) all->var.pos_x][(int) (all->var.pos_y -
													  all->var.plane_y *
													  all->var.move_speed)] ==
			0)
			all->var.pos_y -= all->var.plane_y * all->var.move_speed;
	}
	draw(all);
	return (1);
}

int main()
{
	t_all all;

	int world_map[5][5] =
			{
					{1, 1, 1, 1, 1},
					{1, 0, 0, 0, 1},
					{1, 0, 0, 0, 1},
					{1, 0, 0, 0, 1},
					{1, 1, 1, 1, 1},
			};

	all.var.rot_speed		= 0.05;
	all.var.move_speed		= 0.3;
	all.var.pos_x 			= 3;
	all.var.pos_y			= 3;
	all.var.dir_x			= -1;
	all.var.dir_y			= 0;
	all.var.plane_x			= 0;
	all.var.plane_y			= 0.66;
	all.var.screen_width	= 800;
	all.var.screen_height	= 600;
	
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			all.var.map[i][j] = world_map[i][j];

	all.mlx.mlx				= mlx_init();
	all.mlx.win 			= mlx_new_window(all.mlx.mlx, all.var.screen_width, all.var.screen_height, "hey");

	all.mlx.img 			= mlx_new_image(all.mlx.mlx, all.var.screen_width, all.var.screen_height);
	all.mlx.addr			= mlx_get_data_addr(all.mlx.img, &all.mlx.bits_per_pixel, &all.mlx.line_length, &all.mlx.endian);

	all.text.img			= (void **)malloc(sizeof(void *) * 6);
	all.text.addr			= (char **)malloc(sizeof(char *) * 6);
	all.text.bits_per_pixel = (int *)malloc(sizeof(int) * 6);
	all.text.line_length 	= (int *)malloc(sizeof(int) * 6);
	all.text.endian 		= (int *)malloc(sizeof(int) * 6);
	all.text.width 			= (int *)malloc(sizeof(int) * 6);
	all.text.height 		= (int *)malloc(sizeof(int) * 6);

	all.text.path			= (char **)malloc(sizeof(char*) * 6);
	all.text.path[0]		= (char*)malloc(sizeof(char) * 100);
	all.text.path[1]		= (char*)malloc(sizeof(char) * 100);
	all.text.path[2]		= (char*)malloc(sizeof(char) * 100);
	all.text.path[3]		= (char*)malloc(sizeof(char) * 100);

	all.text.path[0] 		= "../pics/mossy.xpm";
	all.text.path[1] 		= "../pics/redbrick.xpm";
	all.text.path[2] 		= "../pics/wood.xpm";
	all.text.path[3] 		= "../pics/greystone.xpm";

	all.text.img[0] 		= mlx_xpm_file_to_image(all.mlx.mlx, all.text.path[0], &all.text.width[0], &all.text.height[0]);
	all.text.img[1] 		= mlx_xpm_file_to_image(all.mlx.mlx, all.text.path[1], &all.text.width[1], &all.text.height[1]);
	all.text.img[2] 		= mlx_xpm_file_to_image(all.mlx.mlx, all.text.path[2], &all.text.width[2], &all.text.height[2]);
	all.text.img[3] 		= mlx_xpm_file_to_image(all.mlx.mlx, all.text.path[3], &all.text.width[3], &all.text.height[3]);
//	all.text.img[4] 		= mlx_xpm_file_to_image(all.mlx.mlx, all.text.path[4], &all.text.width[4], &all.text.height[4]);

	all.text.addr[0] 		= mlx_get_data_addr(all.text.img[0],
											&all.text.bits_per_pixel[0],
											&all.text.line_length[0],
											&all.text.endian[0]);
	all.text.addr[1] 		= mlx_get_data_addr(all.text.img[1],
										 &all.text.bits_per_pixel[1],
										 &all.text.line_length[1],
										 &all.text.endian[1]);
	all.text.addr[2] 		= mlx_get_data_addr(all.text.img[2],
										 &all.text.bits_per_pixel[2],
										 &all.text.line_length[2],
										 &all.text.endian[2]);
	all.text.addr[3] 		= mlx_get_data_addr(all.text.img[3],
										 &all.text.bits_per_pixel[3],
										 &all.text.line_length[3],
										 &all.text.endian[3]);
//	all.text.addr[4] = mlx_get_data_addr(all.text.img[4],
//										 &all.text.bits_per_pixel[4],
//										 &all.text.line_length[4],
//										 &all.text.endian[4]);

	draw(&all);
	mlx_hook(all.mlx.win, 2, 0, move, &all);
	mlx_loop(all.mlx.mlx);
	exit(0);

	return 0;
}
