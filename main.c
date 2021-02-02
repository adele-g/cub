#include "cub3d.h"
#include "math.h"

void            my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char    *dst;

	dst = all->mlx.addr + (y * all->mlx.line_length + x * (all->mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

		printf("%f   %d\n", all->var.perp_wall_dist, all->var.side);
		all->var.line_height = (int)(all->var.screen_height / all->var.perp_wall_dist);
		all->var.draw_start = -all->var.line_height / 2 + all->var.screen_height / 2;
		if (all->var.draw_start < 0)
			all->var.draw_start = 0;

		all->var.draw_end = all->var.line_height / 2 + all->var.screen_height / 2;
		if (all->var.draw_end >= all->var.screen_height)
			all->var.draw_end = all->var.screen_height - 1;
		all->var.tex_num = all->var.map[all->var.map_x][all->var.map_y] - 1;

		if (all->var.side == 0)
			all->var.wall_x = all->var.pos_y + all->var.perp_wall_dist * all->var.ray_dir_y;
		else
			all->var.wall_x = all->var.pos_x + all->var.perp_wall_dist * all->var.ray_dir_x;
		all->var.wall_x -= floor(all->var.wall_x);


		all->var.tex_x = (int)(all->var.wall_x * (double)all->var.tex_width);
		if (all->var.side == 0 && all->var.ray_dir_x > 0)
			all->var.tex_x = all->var.tex_width - all->var.tex_x - 1;
		if (all->var.side == 1 && all->var.ray_dir_y < 0)
			all->var.tex_x = all->var.tex_width - all->var.tex_width - all->var.tex_x - 1;
		all->var.step = 1.0 * all->var.tex_height / all->var.line_height;
		all->var.tex_pos = (all->var.draw_start - all->var.screen_height / 2 + all->var.line_height / 2) * all->var.step;
		int y = all->var.draw_start;
		while (y < all->var.draw_end)
		{
			all->var.tex_y = (int)all->var.tex_pos & (all->var.tex_height - 1);
			all->var.tex_pos += all->var.step;
			all->var.color = all->var.texture[(int)all->var.tex_num][(int)(all->var.tex_height * all->var.tex_y + all->var.tex_x)];
			if (all->var.side == 1)
				all->var.color = (all->var.color >> 1) & 8355711;
			all->var.buf[y][i] = all->var.color;
			y++;
		}

//		for (int j = 0; j < all->var.draw_start; j++)
//			my_mlx_pixel_put(all, i, j, all->var.color);
//		for (int j = all->var.draw_start; j < all->var.draw_end; j++)
//			my_mlx_pixel_put(all, i, j, all->var.color);
//		for (int j = all->var.draw_end; j < all->var.screen_height; j++)
//			my_mlx_pixel_put(all, i, j, all->var.color);
		i++;
	}
	for (int j = 0; j < all->var.draw_start; j++)
		my_mlx_pixel_put(all, i, j, all->var.color);
	for (int j = all->var.draw_start; j < all->var.draw_end; j++)
		my_mlx_pixel_put(all, i, j, all->var.color);
	for (int j = all->var.draw_end; j < all->var.screen_height; j++)
		my_mlx_pixel_put(all, i, j, all->var.color);


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
//	if (keycode == 123) 124
//	{
//
//	}
	draw(all);
	return (1);
}

int main()
{
	t_all all;

	int world_map[24][24] =
{
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
			{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
			{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
	all.var.tex_width = 64;
	all.var.tex_height = 64;

	all.var.rot_speed = 0.05;
	all.var.move_speed = 0.3;
	all.var.pos_x = 22;
	all.var.pos_y = 12;
	all.var.dir_x = -1;
	all.var.dir_y = 0;
	all.var.plane_x = 0;
	all.var.plane_y = 0.66;
	all.var.screen_width = 640;
	all.var.screen_height = 480;

	all.var.buf = (int **)malloc(sizeof(int) * all.var.screen_height);
	for (int i = 0; i < all.var.screen_height; i++)
	{
		all.var.buf[i] = (int *)malloc(sizeof(int) * all.var.screen_width);
	}

	for (int i = 0; i < all.var.screen_height; i++)
	{
		for (int j = 0; j < all.var.screen_width; j++)
		{
			all.var.buf[i][j] = 0;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < all.var.tex_width * all.var.tex_height; j++)
		{
			all.var.texture[i][j] = 0;
		}
	}
	for (int x = 0; x < all.var.tex_height; x++)
	{
		for (int y = 0; y < all.var.tex_height; y++)
		{
			all.var.xor_color = (x * 256 / all.var.tex_width) ^ (y * 256 / all.var.tex_height);
			all.var.y_color = y * 256 / all.var.tex_height;
			all.var.xy_color = y * 128 / all.var.tex_height + x * 128 / all.var.tex_width;
			all.var.texture[0][64 * y + x] = 65536 * 254 * (x != y && x != all.var.tex_width - y);
			all.var.texture[1][64 * y + x] = all.var.xy_color + 256 * all.var.xy_color + 65536 * all.var.xy_color;
			all.var.texture[2][64 * y + x] = 256 * all.var.xy_color + 65536 * all.var.xy_color;
			all.var.texture[3][64 * y + x] = all.var.xor_color + 256 * all.var.xor_color + 65536 * all.var.xor_color;
			all.var.texture[4][64 * y + x] = 256 * all.var.xor_color;
			all.var.texture[5][64 * y + x] = 65536 * 192 * (x % 16 && y % 16);
			all.var.texture[6][64 * y + x] = 65536 * all.var.y_color;
			all.var.texture[7][64 * y + x] = 128 + 256 * 128 + 65536 * 128;
		}
	}


	for (int i = 0; i < 24; i++)
		for (int j = 0; j < 24; j++)
			all.var.map[i][j] = world_map[i][j];

	all.mlx.mlx = mlx_init();
	all.mlx.win = mlx_new_window(all.mlx.mlx, all.var.screen_width, all.var.screen_height, "hey");
	all.mlx.img = mlx_new_image(all.mlx.mlx, all.var.screen_width, all.var.screen_height);
	all.mlx.addr = mlx_get_data_addr(all.mlx.img, &all.mlx.bits_per_pixel, &all.mlx.line_length, &all.mlx.endian);


	draw(&all);
	mlx_hook(all.mlx.win, 2, 0, move, &all);
	mlx_loop(all.mlx.mlx);
	exit(0);

	return 0;
}
