#include "cub3d.h"

void	init(t_all *all)
{
	ft_init_raycasting(all);
	init_mlx(all);
	init_img_mlx(all);
}

void	init_textures(t_all *all)
{
	int i;

	i = -1;
	while (++i <= 4)
	{
		if (!(all->text.img[i] = mlx_xpm_file_to_image(all->mlx.mlx,
												all->text.path[i],
												&all->text.width[i],
												&all->text.height[i])))
			ft_exit("wrong path", all);
		if (!(all->text.addr[i] = mlx_get_data_addr(all->text.img[i],
			&all->text.bits_per_pixel[i], &all->text.line_length[i],
			&all->text.endian[i])))
			ft_exit("wrong path", all);
	}
}

void	init_img_mlx(t_all *all)
{
	all->text.img = (void **)malloc(sizeof(void *) * 6);
	all->text.addr = (char **)malloc(sizeof(char *) * 6);
	all->text.bits_per_pixel = (int *)malloc(sizeof(int) * 6);
	all->text.line_length = (int *)malloc(sizeof(int) * 6);
	all->text.endian = (int *)malloc(sizeof(int) * 6);
	all->text.width = (int *)malloc(sizeof(int) * 6);
	all->text.height = (int *)malloc(sizeof(int) * 6);
}

void	init_mlx(t_all *all)
{
	all->mlx.mlx = mlx_init();
	all->mlx.win = mlx_new_window(all->mlx.mlx, all->var.screen_width,
	all->var.screen_height, "cub3D");
	all->mlx.img = mlx_new_image(all->mlx.mlx, all->var.screen_width,
	all->var.screen_height);
	all->mlx.addr = mlx_get_data_addr(all->mlx.img, &all->mlx.bits_per_pixel,
	&all->mlx.line_length, &all->mlx.endian);
}

void	ft_init_raycasting(t_all *all)
{
	all->var.rot_speed = 0.1;
	all->var.move_speed = 0.3;
	all->var.zbuffer = (double *)malloc(sizeof(double) *
	all->var.screen_width);
}
