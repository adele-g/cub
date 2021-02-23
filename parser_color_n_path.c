#include "parser.h"

int				ft_atoi_color(char *str)
{
	int		res;
	int		sign;

	sign = 1;
	res = 0;
	if (*str == '\0' || *str == ',')
		return (-1);
	while (*str == ' ' || *str == '\t' || *str == '\n'
		   || *str == '\v' || *str == '\f' || *str == '\r' || *str == ',')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		res = res * 10 + *str++ - '0';
	return (res * sign);
}

void			parser_celling_color(char *data, t_all *all)
{
	data++;
	data = remove_space(data);
	if ((check_value(data)) == -1)
		ft_exit("trash in value of celling color");
	all->var.c_color.r = ft_atoi_color(data);
	data = remove_num(data);
	data = remove_space(data);
	data = remove_comma(data);
	data = remove_space(data);
	all->var.c_color.g = ft_atoi_color(data);
	data = remove_num(data);
	data = remove_space(data);
	data = remove_comma(data);
	data = remove_space(data);
	all->var.c_color.b = ft_atoi_color(data);
	while (*data >= '0' && *data <= '9')
		data++;
	while (*data != '\0')
		if (*data++ != ' ')
			ft_exit("wrong value after celling color");
	all->var.flag += 0.0000001;
	if ((all->var.c_color.r < 0 || all->var.c_color.r > 255) ||
		(all->var.c_color.g < 0 || all->var.c_color.g > 255) ||
		(all->var.c_color.b < 0 || all->var.c_color.b > 255))
		ft_exit("wrong celling color");
}

void			parser_floor_color(char *data, t_all *all)
{
	data++;
	data = remove_space(data);
	if ((check_value(data)) == -1)
		ft_exit("trash in value of flooring color");
	all->var.f_color.r = ft_atoi_color(data);
	data = remove_num(data);
	data = remove_space(data);
	data = remove_comma(data);
	data = remove_space(data);
	all->var.f_color.g = ft_atoi_color(data);
	data = remove_num(data);
	data = remove_space(data);
	data = remove_comma(data);
	data = remove_space(data);
	all->var.f_color.b = ft_atoi_color(data);
	data = remove_num(data);
	while (*data != '\0')
		if (*data++ != ' ')
			ft_exit("wrong value after floor color");
	all->var.flag += 0.000001;
	if ((all->var.f_color.r < 0 || all->var.f_color.r > 255) ||
		(all->var.f_color.g < 0 || all->var.f_color.g > 255) ||
		(all->var.f_color.b < 0 || all->var.f_color.b > 255))
		ft_exit("wrong flooring color");
}

void			parser_path(char *data, t_all *all, int i)
{
	int k;

	k = 0;
	data = remove_name(data);
	data = remove_space(data);
	if (*data == '\0')
		ft_exit("trashy path");
	if (check_n(data))
	{
		while (data[k] != '\n')
			k++;
		if (data[k] == '\n')
			data[k] = '\0';
	}
	if (check_xpm(data) == -1)
		ft_exit("not xpm file");
	all->text.path[i] = data;
	(i == 0) ? all->var.flag += 0.00001 : all->var.flag;
	(i == 1) ? all->var.flag += 0.0001 : all->var.flag;
	(i == 2) ? all->var.flag += 0.001 : all->var.flag;
	(i == 3) ? all->var.flag += 0.01 : all->var.flag;
	(i == 4) ? all->var.flag += 0.1 : all->var.flag;
}