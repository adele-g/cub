#include "parser.h"

void			parser_map(t_all *all)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < all->var.num_of_colum)
	{
		if ((check_data(all->var.map[i])) == -1)
			ft_exit("trash in map", all);
		i++;
	}
	i = 0;
	while (all->var.map[i][0] == '\0')
	{
		i++;
		all->var.num_of_eof++;
	}
	i++;
	if (all->var.num_of_colum - all->var.num_of_eof < 3)
		ft_exit("too little lines for playing", all);
	if (check_first_line(all, i, j) == -1)
		ft_exit("unclosed map", all);
	check_all_map(all, i);
}

void			make_map(t_all *all, char *data)
{
	if (!(all->var.map[all->var.num_of_colum] =
			ft_calloc(all->var.num_of_char, sizeof(char))))
		ft_exit("malloc", all);
	ft_strcpy(all->var.map[all->var.num_of_colum], data);
	all->var.num_of_colum++;
}

int				count_line_breaks(t_all *all, int fd)
{
	char	*buf;

	if ((get_next_line(fd, &buf)) == -1)
	{
		count_chars(buf, all);
		free(buf);
		return (-1);
	}
	while ((get_next_line(fd, &buf)) > 0)
	{
		count_chars(buf, all);
		all->var.line_breaks++;
		free(buf);
	}
	count_chars(buf, all);
	free(buf);
	all->var.line_breaks += 3;
	return (all->var.line_breaks);
}

int				ft_check_cub(const char *data)
{
	int i;

	i = 0;
	while (data[i] != '\0')
		i++;
	i--;
	if (data[i] == 'b' && data[i - 1] == 'u' && data[i - 2] == 'c' &&
		data[i - 3] == '.')
		return (1);
}
