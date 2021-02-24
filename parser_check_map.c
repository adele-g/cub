#include "parser.h"

int				check_from_top_to_bottom(t_all *all, int i)
{
	int j;

	j = 0;
	i--;
	while (i - all->var.num_of_eof + 1)
	{
		j = 0;
		while (all->var.map[i][j])
			j++;
		if (j != 0)
			j--;
		if (all->var.map[i][j] == '1' || all->var.map[i][j] == ' ' ||
			all->var.map[i][j] == '\0')
		{
			if (i == all->var.num_of_colum - 1 && all->var.map[i][0] == '\0')
				i--;
			i--;
		}
		else
			return (-1);
	}
	return (1);
}

void			check_inside_map(t_all *all, int i, int j)
{
	int x;
	int y;

	y = -1;
	while (y != 2)
	{
		x = -1;
		while (x != 2)
		{
			if (all->var.map[i + y][j + x] == ' ' ||
				all->var.map[i + y][j + x] == '\0')
				ft_exit("wrong map", all);
			x++;
		}
		y++;
	}
}

void			check_in_map(t_all *all, int i)
{
	int j;

	while (all->var.map[i])
	{
		j = 0;
		while (all->var.map[i][j])
		{
			if (all->var.map[i][j] == '0' || all->var.map[i][j] == '2' ||
				all->var.map[i][j] == 'S' || all->var.map[i][j] == 'W' ||
				all->var.map[i][j] == 'E' || all->var.map[i][j] == 'N')
				check_inside_map(all, i, j);
			j++;
		}
		i++;
	}
	if (check_last_line(all, i) == -1)
		ft_exit("broken last line", all);
	if (check_from_top_to_bottom(all, i) == -1)
		ft_exit("broken map in last row", all);
}

int				check_first_row(t_all *all, int i)
{
	while (all->var.map[i])
	{
		if (all->var.map[i][0] == '1' || all->var.map[i][0] == ' ' ||
			all->var.map[i][0] == '\0')
		{
			if (i == all->var.num_of_colum - 1 && all->var.map[i][0] == '\0')
				i++;
			i++;
		}
		else
			return (-1);
	}
	return (1);
}

void			check_all_map(t_all *all, int i)
{
	if (check_map_eof(all, i) == -1)
		ft_exit("we can't use broken map", all);
	if (check_player(all, i) != 1)
		ft_exit("something wrong with player", all);
	if (check_first_row(all, i) == -1)
		ft_exit("broken map", all);
	if (check_sprite(all, i) == -1)
		ft_exit("no sprites", all);
	all->sprite = ft_calloc(all->var.num_sprites, sizeof(t_sprite));
	find_sprite(all, i);
	check_in_map(all, i);
}
