#include "cub3d.h"

void 	draw(t_all *all)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (i < all->var.screen_width - 1)
		raycasting_n_draw(all, i++);
	find_distance(all);
	sort(all);
	while (k < all->var.num_sprites)
	{
		sprite_count(all, k);
		sprite_count_draw(all);
		while (all->var.stripe < all->var.drawn_end_x - 1)
		{
			sprite_draw(all);
			all->var.stripe++;
		}
		k++;
	}
	mlx_put_image_to_window(all->mlx.mlx, all->mlx.win, all->mlx.img, 0,
						 0);
}

int		main(int argc, char **argv)
{
	t_all all;

	if (argc < 2 || argc > 3)
		ft_exit("argc", &all);
	if (ft_check_cub(argv[1]))
	{
		ft_init_parser(&all);
		ft_parser(argv[1], &all);
	}
	init(&all);
	init_textures(&all);
	draw(&all);
	if (argc == 3 && (check_save(argv[2]) == 1))
		create_bmp(&all);
	mlx_hook(all.mlx.win, 2, 0, move, &all);
	mlx_hook(all.mlx.win, 17, 17, ft_close, &all);
	mlx_loop(all.mlx.mlx);
	ft_free(&all);
	exit(1);
}