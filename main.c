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

//void insert_sort(int **mass, size_t len_mas)
//{
//	int i = 1;
//	int tmp;
//	int j = 0;
//
//	while (i <  len_mas)
//	{
//		j = i;
//		while (j > 0 && mass[j] < mass[j - 1])
//		{
//			tmp = mass[j];
//			mass[j] = mass[j - 1];
//			mass[j - 1] = tmp;
//			j -= 1;
//		}
//		i++;
//	}
//}

void 	draw(t_all *all)
{
	int i = 0;
	while (i < all->var.screen_width)
	{
		all->var.camera_x = 2 * i / (double) (all->var.screen_width) - 1;
		all->var.ray_dir_x =
				all->var.dir_x + all->var.plane_x * all->var.camera_x;
		all->var.ray_dir_y =
				all->var.dir_y + all->var.plane_y * all->var.camera_x;
		all->var.side_dist_x = fabs(1 / all->var.ray_dir_x);
		all->var.side_dist_y = fabs(1 / all->var.ray_dir_y);
		all->var.hit = 0;
		all->var.delta_dist_x = (all->var.ray_dir_y == 0) ? 0
														  : ((all->var.ray_dir_x ==
															  0) ? 1 : fabs(
						1 / all->var.ray_dir_x));
		all->var.delta_dist_y = (all->var.ray_dir_x == 0) ? 0
														  : ((all->var.ray_dir_y ==
															  0) ? 1 : fabs(
						1 / all->var.ray_dir_y));
		all->var.map_x = (int) all->var.pos_x;
		all->var.map_y = (int) all->var.pos_y;

		if (all->var.ray_dir_x < 0)
		{
			all->var.step_x = -1;
			all->var.side_dist_x =
					(all->var.pos_x - all->var.map_x) * all->var.delta_dist_x;
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
			all->var.side_dist_y =
					(all->var.pos_y - all->var.map_y) * all->var.delta_dist_y;
		}
		else
		{
			all->var.step_y = 1;
			all->var.side_dist_y = (all->var.map_y + 1.0 - all->var.pos_y) *
								   all->var.delta_dist_y;
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
			if (all->var.map[all->var.map_x][all->var.map_y] == '1')//'1'
				all->var.hit = 1;
		}


		if (all->var.side == 0)
			all->var.perp_wall_dist = (all->var.map_x - all->var.pos_x +
									   (1 - all->var.step_x) / 2) /
									  all->var.ray_dir_x;
		else
			all->var.perp_wall_dist = (all->var.map_y - all->var.pos_y +
									   (1 - all->var.step_y) / 2) /
									  all->var.ray_dir_y;

		all->var.line_height = (int) (all->var.screen_height /
									  all->var.perp_wall_dist);
		all->var.draw_start =
				-all->var.line_height / 2 + all->var.screen_height / 2;
//		if (all->var.draw_start < 0)
//			all->var.draw_start = 0;

		all->var.draw_end =
				all->var.line_height / 2 + all->var.screen_height / 2;
		if (all->var.draw_end >= all->var.screen_height)
			all->var.draw_end = all->var.screen_height - 1;

//		all->var.tex_num = all->var.map[all->var.map_y][all->var.map_x] - 1;

		if (all->var.side == 0)
			all->var.wall_x = all->var.pos_y +
							  all->var.perp_wall_dist * all->var.ray_dir_y;
		else
			all->var.wall_x = all->var.pos_x +
							  all->var.perp_wall_dist * all->var.ray_dir_x;

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

		all->var.tex_x = (int) (all->var.wall_x *
								(double) (all->text.width[j]));

		all->var.step =
				1.0 * (all->text.height[j] / (int) all->var.line_height);


		all->var.tex_pos = (all->var.draw_start - all->var.screen_height / 2 +
							all->text.line_length[j] / 2) * all->var.step;
		while (y < all->var.screen_height - 1)
		{

			if (y < all->var.draw_start)
				my_mlx_pixel_put(all, i, y, 0x000823492);
			else if (y >= all->var.draw_start && y <= all->var.draw_end)
			{
				all->text.coef = (float) all->var.line_height /
								 (float) all->text.height[j];
				all->var.tex_y = (float) (y - all->var.draw_start);
				all->var.tex_y = all->var.tex_y / all->text.coef;
				if (all->var.tex_y > all->text.height[j])
					all->var.tex_y = all->text.height[j] - 1;
				all->var.dst = all->mlx.addr + (y * all->mlx.line_length + i *
																		   (all->mlx.bits_per_pixel /
																			8));
				all->var.src = all->text.addr[j] + ((int) all->var.tex_y *
													all->text.line_length[j] +
													all->var.tex_x *
													(all->text.bits_per_pixel[j] /
													 8));
				*(unsigned int *) all->var.dst = *(unsigned int *) all->var.src;
			}
			else
				my_mlx_pixel_put(all, i, y, 0x0093874);
			y++;
		}
		all->var.zbuffer[y] = all->var.perp_wall_dist;
		i++;
	}

//	int y = 0;
//	int k = 0;
//	while (k < all->var.num_sprites)
//	{
//		all->var.sprite_order[k] = k;
//		all->var.sprite_distance[k] = (
//				((all->var.pos_x - all->var.sprite[k][0]) *
//				 (all->var.pos_x - all->var.sprite[k][0])) +
//				(all->var.pos_y - all->var.sprite[k][1]) *
//				(all->var.pos_y - all->var.sprite[k][1]));
//
////		printf("%f\n", all->var.sprite_distance[k]);
//		k++;
//	}
////	//insert_sort(all->var.sprite, all->var.num_sprites);
//	k = 0;
//	while (k < all->var.num_sprites)
//	{
//		all->var.sprite_x =
//				all->var.sprite[all->var.sprite_order[k]][0] - all->var.pos_x;
//		all->var.sprite_y =
//				all->var.sprite[all->var.sprite_order[k]][1] - all->var.pos_y;
////		printf("%f %f \n", all->var.sprite_x, all->var.sprite_y);
//		all->var.inv_det = 1.0 / (all->var.plane_x * all->var.dir_y -
//								  all->var.dir_x * all->var.plane_y);
//		all->var.transfor_x = all->var.inv_det *
//							  (all->var.dir_y * all->var.sprite_x -
//							   all->var.dir_x * all->var.sprite_y);
//		all->var.transfor_y = all->var.inv_det *
//							  (-all->var.plane_y * all->var.sprite_x +
//							   all->var.plane_x * all->var.sprite_y);
//
//		all->var.sprite_screen_x = (int)((all->var.screen_width / 2) * (1 +
//																		 all->var.transfor_x /
//																		 all->var.transfor_y));
//		all->var.sprite_height = abs((int)(all->var.screen_height / all->var.transfor_y));
//		all->var.draw_start_y = -all->var.sprite_height / 2 + all->var.screen_height / 2;
//		if (all->var.draw_start_y < 0)
//			all->var.draw_start_y = 0;
//		printf("%d\n", all->var.draw_start_y);
//		all->var.draw_end_y = all->var.sprite_height / 2 + all->var.screen_height / 2;
//		if (all->var.draw_end_y >= all->var.screen_height)
//			all->var.draw_end_y = all->var.screen_height - 1;
//
//		all->var.sprite_width = fabs((int) all->var.screen_height / (all->var.transfor_y));
//
//		all->var.draw_start_x = -all->var.sprite_width / 2 + all->var.sprite_screen_x;
//		if (all->var.draw_start_x < 0)
//			all->var.draw_start_x = 0;
//		all->var.drawn_end_x = all->var.sprite_width / 2 + all->var.sprite_screen_x;
//		if (all->var.drawn_end_x >= all->var.screen_width)
//			all->var.drawn_end_x = all->var.screen_width - 1;
//
//		all->var.stripe = all->var.draw_start_x;
//		while (all->var.stripe < all->var.drawn_end_x)
//		{
//			all->var.tex_x = (int) (256 * (all->var.stripe - (-all->var.sprite_width / 2 + all->var.sprite_screen_x)) * all->text.width[4] / all->var.sprite_width) / 256;
////			printf("%d\n", all->var.tex_x);
//			y = all->var.draw_start_y;
//			if (all->var.transfor_y > 0 && all->var.stripe > 0 && all->var.stripe < all->var.screen_width && all->var.transfor_y < all->var.zbuffer[all->var.stripe])
//			{
//				while (y < all->var.draw_end_y)
//				{
//					all->text.coef = (float) all->var.line_height /
//									 (float) all->text.height[4];
//					all->var.tex_y = (float) (y - all->var.draw_start_y);
//					all->var.tex_y = all->var.tex_y / all->text.coef;
//					if (all->var.tex_y > all->text.height[4])
//						all->var.tex_y = all->text.height[4] - 1;
////					printf("%f\n", all->text.coef);
//					all->var.dst = all->mlx.addr + (y * all->mlx.line_length +
//													i *
//													(all->mlx.bits_per_pixel /
//													 8));
//					all->var.src = all->text.addr[4] + ((int) all->var.tex_y *
//														all->text.line_length[4] +
//														all->var.tex_x *
//														(all->text.bits_per_pixel[4] /
//														 8));
//					*(unsigned int *)all->var.dst = *(unsigned int *)all->var.src;
////					printf("%s \n", all->text.addr[4]);
//					y++;
//				}
//			}
//			all->var.stripe++;
//		}
//		k++;
//	}
	mlx_put_image_to_window(all->mlx.mlx, all->mlx.win, all->mlx.img, 0, 0);
}

int move(int keycode, t_all *all)
{
	if (keycode == 13)
	{
		if (all->var.map[(int) (all->var.pos_x + all->var.dir_x *
												 all->var.move_speed)][(int) all->var.pos_y] == '0') //'0'
			all->var.pos_x += all->var.dir_x * all->var.move_speed;
		if (all->var.map[(int) all->var.pos_x][(int) (all->var.pos_y +
													  all->var.dir_y *
													  all->var.move_speed)] ==
			'0')
			all->var.pos_y += all->var.dir_y * all->var.move_speed;
	}
	if (keycode == 1)
	{
		if (all->var.map[(int) (all->var.pos_x - all->var.dir_x *
												 all->var.move_speed)][(int) all->var.pos_y] ==
			'0')
			all->var.pos_x -= all->var.dir_x * all->var.move_speed;
		if (all->var.map[(int) all->var.pos_x][(int) (all->var.pos_y -
													  all->var.dir_y *
													  all->var.move_speed)] ==
			'0')
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
		mlx_destroy_window(all->mlx.mlx, all->mlx.win);
		exit(0);
	}
	if (keycode == 124)
	{
		if (all->var.map[(int) (all->var.pos_x + all->var.plane_x *
												 all->var.move_speed)][(int) all->var.pos_y] ==
			'0')
			all->var.pos_x += all->var.plane_x * all->var.move_speed;
		if (all->var.map[(int) all->var.pos_x][(int) (all->var.pos_y +
													  all->var.plane_y *
													  all->var.move_speed)] ==
			'0')
			all->var.pos_y += all->var.plane_y * all->var.move_speed;
	}
	if (keycode == 123)
	{
		if (all->var.map[(int) (all->var.pos_x - all->var.plane_x *
												 all->var.move_speed)][(int) all->var.pos_y] ==
			'0')
			all->var.pos_x -= all->var.plane_x * all->var.move_speed;
		if (all->var.map[(int) all->var.pos_x][(int) (all->var.pos_y -
													  all->var.plane_y *
													  all->var.move_speed)] ==
			'0')
			all->var.pos_y -= all->var.plane_y * all->var.move_speed;
	}
	draw(all);
	return (1);
}

int ft_close(t_all *all)
{
	mlx_destroy_window(all->mlx.mlx, all->mlx.win);
	exit(0);
}

void ft_init_raycasting(t_all *all)
{
	all->var.rot_speed		= 0.1;
	all->var.move_speed		= 0.5;
//	all->var.dir_x			= -1;
//	all->var.dir_y			= 0;
//	all->var.plane_x		= 0;
//	all->var.plane_y		= 0.66;
	all->var.zbuffer = (double *) malloc(sizeof(double) * all->var.screen_width);
}

void set_player(t_all *all, char name)
{
	if (name == 'N')
	{
		all->var.dir_x = -1;
		all->var.plane_y = 0.66;
	}
	else if (name == 'S')
	{
		all->var.dir_x = 1;
		all->var.plane_y = -0.66;
	}
	else if (name == 'W')
	{
		all->var.dir_x = -1;
		all->var.plane_y = -0.66;
	}
	else if (name == 'E')
	{
		all->var.dir_y = 1;
		all->var.plane_x = 0.66;
	}
}

void init_mlx(t_all *all)
{
	all->mlx.mlx = mlx_init();
	all->mlx.win = mlx_new_window(all->mlx.mlx, all->var.screen_width,
							   all->var.screen_height, "cub3D");
	all->mlx.img = mlx_new_image(all->mlx.mlx, all->var.screen_width,
							  all->var.screen_height);
	all->mlx.addr = mlx_get_data_addr(all->mlx.img, &all->mlx.bits_per_pixel,
								   &all->mlx.line_length, &all->mlx.endian);
}

void init_img_mlx(t_all *all)
{
	all->text.img			= (void **)malloc(sizeof(void *) * 6);
	all->text.addr			= (char **)malloc(sizeof(char *) * 6);
	all->text.bits_per_pixel = (int *)malloc(sizeof(int) * 6);
	all->text.line_length 	= (int *)malloc(sizeof(int) * 6);
	all->text.endian 		= (int *)malloc(sizeof(int) * 6);
	all->text.width 		= (int *)malloc(sizeof(int) * 6);
	all->text.height 		= (int *)malloc(sizeof(int) * 6);
}

void init_sprite(t_all *all)
{
	all->var.num_sprites		= 1;

	all->var.sprite_order 	= (int*)malloc(sizeof(int) * all->var.num_sprites);
	all->var.sprite_distance = (float*)malloc(sizeof(float) * all->var.num_sprites);
	all->var.sprite			= (float**)malloc(sizeof(float*) * all->var.num_sprites);
}

void init_path(t_all *all)
{
	int i;

	i = -1;
	all->text.path			= (char **)malloc(sizeof(char*) * 6);
	while (++i < 4)
		all->text.path[i]		= (char*)malloc(sizeof(char) * 100);
}

void init_textures(t_all *all)
{
	int i;

	i = -1;
	while (++i <= 4)
	{
		all->text.img[i] = mlx_xpm_file_to_image(all->mlx.mlx,
												 all->text.path[i],
												 &all->text.width[i],
												 &all->text.height[i]);
		all->text.addr[i] = mlx_get_data_addr(all->text.img[i],
													 &all->text.bits_per_pixel[i],
													 &all->text.line_length[i],
													 &all->text.endian[i]);
	}

}

void init_text(t_all *all)
{
	init_img_mlx(all);
//	init_sprite(all);

}

void init(t_all *all)
{
	ft_init_raycasting(all);
	init_mlx(all);
	init_text(all);

}
int main(int argc, char **argv)
{
	t_all all;

	if (argc < 2 || argc > 3)
		ft_exit("argc");

	if (ft_check_cub(argv[1]) && argc == 2)
	{
		ft_init_parser(&all);
		ft_parser(argv[1], &all);
	}
	init(&all);
	init_textures(&all);
	draw(&all);
	mlx_hook(all.mlx.win, 2, 0, move, &all);
	mlx_hook(all.mlx.win, 17, 17, ft_close, &all);
	mlx_loop(all.mlx.mlx);
	mlx_destroy_image(all.mlx.mlx, all.mlx.img);
	exit(0);

	return 0;
}
