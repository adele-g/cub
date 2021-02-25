#include "parser.h"

void			ft_init_parser(t_all *all)
{
	all->var.screen_width = -1;
	all->var.screen_height = -1;
	all->var.line_breaks = 0;
	all->var.num_of_colum = 0;
	all->var.flag = 1.00000000;
	all->var.num_sprites = 0;
	all->var.num_of_eof = 0;
	all->var.num_of_char = 0;
	if (!(all->text.path = (char **)malloc(sizeof(char*) * 6)))
		ft_exit("malloc", all);
	if (!(all->text.path[0] = (char*)malloc(sizeof(char) * 100)))
		ft_exit("malloc", all);
	if (!(all->text.path[1] = (char*)malloc(sizeof(char) * 100)))
		ft_exit("malloc", all);
	if (!(all->text.path[2] = (char*)malloc(sizeof(char) * 100)))
		ft_exit("malloc", all);
	if (!(all->text.path[3] = (char*)malloc(sizeof(char) * 100)))
		ft_exit("malloc", all);
	if (!(all->text.path[4] = (char*)malloc(sizeof(char) * 100)))
		ft_exit("malloc", all);
	init_color(&all->var.c_color);
	init_color(&all->var.f_color);
}

void			ft_exit(char *str, t_all *all)
{
	write(1, "Error\n", 6);
	write(1, str, ft_strlen(str) + 1);
	write(1, "\n", 1);
	(void)all;
	exit(1);
}

void			init_color(t_color *color)
{
	color->r = -1;
	color->g = -1;
	color->b = -1;
}

void			ft_parser(char *file, t_all *all)
{
	char	**data;
	int		fd;
	int		i;

	i = 0;
	fd = 0;
	check_fd(fd, file, all);
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit("wrong file", all);
	if (!((data = ft_calloc(all->var.line_breaks - 1, sizeof(char*))) &&
	(all->var.map = ft_calloc(all->var.line_breaks, sizeof(char*)))))
		ft_exit("malloc", all);
	while (i < all->var.line_breaks - 1)
	{
		get_next_line(fd, &data[i]);
		find_spec(data[i], all);
		free(data[i]);
		i++;
	}
	free(data);
	close(fd);
	if (all->var.flag == 1.11111111)
		parser_map(all);
	else
		ft_exit("you've added wrong numbers of arguments", all);
}

void check_fd(int fd, char *file, t_all *all)
{
	if ((fd = open(file, O_DIRECTORY)) != -1)
		ft_exit("you've chosen an directory", all);
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit("wrong file", all);
	if ((all->var.line_breaks = count_line_breaks(all, fd)) == -1)
		ft_exit("something wrong with file", all);
	close(fd);
}
