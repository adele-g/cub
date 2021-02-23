#include "parser.h"

int				check_resolution(t_all *all)
{
	if (all->var.screen_width > 2560)
		all->var.screen_width = 2560;
	if (all->var.screen_height > 1440)
		all->var.screen_height = 1440;
	if (all->var.screen_width <= 0 || all->var.screen_height <= 0)
		return (-1);
	return (1);
}

int				check_value(const char *data)
{
	int i;

	i = 0;
	while (data[i] != '\0')
	{
		if ((data[i] >= '0' && data[i] <= '9') || data[i] == ' ' ||
			data[i] == ',')
			i++;
		else
			return (-1);
	}
	return (1);
}

void			parser_resolution(char *data, t_all *all)
{
	data++;
	data = remove_space(data);
	if ((check_value(data)) == -1)
		ft_exit("trash in value of resolution");
	all->var.screen_width = ft_atoi(data);
	data = remove_num(data);
	data = remove_space(data);
	all->var.screen_height = ft_atoi(data);
	data = remove_num(data);
	while (*data != '\0')
	{
		if (*data++ != ' ')
			ft_exit("wrong value after resolution");
	}
	all->var.flag += 0.00000001;
	if ((check_resolution(all)) == -1)
		ft_exit("wrong resolution");
}

long int		ft_atoi(char *str)
{
	long int		res;
	int				sign;

	sign = 1;
	res = 0;
	if (*str == '\0')
		return (-1);
	while (*str == ' ' || *str == '\t' || *str == '\n'
		   || *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		res = res * 10 + *str++ - '0';
	if (res >= 2147483647)
		res = 2147483647;
	return (res * sign);
}

