#include "cub3d.h"

void	find_sprite(t_all *all, int i)
{
	int j;
	int z;

	z = 0;
	while (all->var.map[i])
	{
		j = 0;
		while (all->var.map[i][j])
		{
			if (all->var.map[i][j] == '2')
			{
				all->sprite[z].x = i;
				all->sprite[z].y = j;
				z++;
			}
			j++;
		}
		i++;
	}
}

void	find_distance(t_all *all)
{
	int i;

	i = 0;
	while (i < all->var.num_sprites)
	{
		all->sprite[i].distance = sqrt(((all->var.pos_x - all->sprite[i].x) *
		(all->var.pos_x - all->sprite[i].x)) +
		(all->var.pos_y - all->sprite[i].y) *
		(all->var.pos_y - all->sprite[i].y));
		i++;
	}
}

void	sort(t_all *all)
{
	t_sort sort;

	sort.i = 1;
	while (sort.i < all->var.num_sprites)
	{
		sort.j = 0;
		while (sort.j < all->var.num_sprites - sort.i)
		{
			if (all->sprite[sort.j].distance < all->sprite[sort.j + 1].distance)
			{
				sort.tmp_x = all->sprite[sort.j].x;
				sort.tmp_y = all->sprite[sort.j].y;
				sort.tmp_dist = all->sprite[sort.j].distance;
				all->sprite[sort.j].distance = all->sprite[sort.j + 1].distance;
				all->sprite[sort.j].x = all->sprite[sort.j + 1].x;
				all->sprite[sort.j].y = all->sprite[sort.j + 1].y;
				all->sprite[sort.j + 1].distance = sort.tmp_dist;
				all->sprite[sort.j + 1].x = sort.tmp_x;
				all->sprite[sort.j + 1].y = sort.tmp_y;
			}
			sort.j++;
		}
		sort.i++;
	}
}

void	set_player(t_all *all, char name)
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
