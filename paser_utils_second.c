#include "parser.h"

char			*remove_name(char *data)
{
	while (*data == 'N' || *data == 'O' || *data == 'S' || *data == 'W' ||
		   *data == 'E' || *data == 'S' || *data == 'A')
		data++;
	return (data);
}

int				check_n(const char *data)
{
	int i;

	i = 0;
	while (data[i] != '\0')
	{
		if (data[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int				check_xpm(const char *data)
{
	int i;

	i = 0;
	while (data[i] != '\0')
		i++;
	i--;
	if (data[i] == 'm' && data[i - 1] == 'p' && data[i - 2] == 'x' &&
		data[i - 3] == '.')
		return (1);
	return (-1);
}

int				check_data(const char *data)
{
	int i;

	i = 0;
	while (data[i] != '\0')
	{
		if (data[i] == '0' || data[i] == '1' || data[i] == '2' || data[i] == 'N'
			|| data[i] == 'S' || data[i] == 'W' || data[i] == 'E' || data[i] == '\n'
			|| data[i] == ' ' || data[i] == '\t' || data[i] == '\v'
			|| data[i] == '\f' || data[i] == '\r')
			i++;
		else
			return (-1);
	}
	if (data[i] == '\0')
		return (1);
	return (1);
}

int				ft_max(int x, int y)
{
	return ((x > y) ? x : y);
}
