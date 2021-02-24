#include "parser.h"

void			find_spec(char *data, t_all *all)
{
	int i;

	i = 0;
	if (data[i] == 'R')
		parser_resolution(data, all);
	else if (data[i] == 'C')
		parser_celling_color(data, all);
	else if (data[i] == 'F')
		parser_floor_color(data, all);
	else if (data[i] == 'N' && data[i + 1] == 'O')
		parser_path(data, all, 0);
	else if (data[i] == 'S' && data[i + 1] == 'O')
		parser_path(data, all, 1);
	else if (data[i] == 'W' && data[i + 1] == 'E')
		parser_path(data, all, 2);
	else if (data[i] == 'E' && data[i + 1] == 'A')
		parser_path(data, all, 3);
	else if (data[i] == 'S')
		parser_path(data, all, 4);
	else if (data[i] == '1' || data[i] == '0' || data[i] == ' ' ||
	data[i] == '\0')
		make_map(all, data);
	else if (!(data[i] == '1' || data[i] == '0' || data[i] == ' ' ||
	data[i] == '\n' || data[i] == '\0'))
		ft_exit("invalid characters", all);
}

void			count_chars(char *data, t_all *all)
{
	all->var.num_of_char = ft_max(all->var.num_of_char, ft_strlen(data));
}
