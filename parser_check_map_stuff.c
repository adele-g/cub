#include "parser.h"


int				check_first_line(t_all *all, int i, int j)
{
	i--;
	while (all->var.map[i][j] != '\0')
	{
		if (all->var.map[i][j] == '1' || all->var.map[i][j] == ' ')
			j++;
		else
			return (-1);
	}
	return (1);
}

int				check_map_eof(t_all *all, int i)
{
	while (all->var.map[i])
	{
		if (all->var.map[i][0] == '\0')
		{
			if (i != all->var.num_of_colum - 1)
				return (-1);
		}
		i++;
	}
	return (1);
}

int				check_player(t_all *all, int i)
{
	int j;
	int res;

	res = 0;
	while (all->var.map[i])
	{
		j = 0;
		while (all->var.map[i][j])
		{
			if (all->var.map[i][j] == 'S' || all->var.map[i][j] == 'W' ||
				all->var.map[i][j] == 'E' || all->var.map[i][j] == 'N')
			{
				res++;
				all->var.pos_x = i;
				all->var.pos_y = j;
				set_player(all, all->var.map[i][j]);
				all->var.map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (res);
}

int				check_sprite(t_all *all, int i)
{
	int j;
	int res;

	res = 0;
	while (all->var.map[i])
	{
		j = 0;
		while (all->var.map[i][j])
		{
			if (all->var.map[i][j] == '2')
				res++;
			j++;
		}
		i++;
	}
	return (res);
}

int				check_last_line(t_all *all, int i)
{
	int j;

	j = 0;
	i--;
	while (all->var.map[i][j])
	{
		if (all->var.map[i][j] == '1' || all->var.map[i][j] == ' ')
			j++;
		else
			return (-1);
	}
	return (1);
}