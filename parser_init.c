#include "parser.h"

void			ft_init_parser(t_all *all)
{
	all->var.screen_width = -1;
	all->var.screen_height = -1;
	all->var.line_breaks = 0;
	all->var.num_of_colum = 0;
	all->var.flag = 1.00000000;
	all->var.num_of_eof = 0;
	all->var.num_of_char = 0;
	all->text.path = (char **)malloc(sizeof(char*) * 6);
	all->text.path[0] = (char*)malloc(sizeof(char) * 100);
	all->text.path[1] = (char*)malloc(sizeof(char) * 100);
	all->text.path[2] = (char*)malloc(sizeof(char) * 100);
	all->text.path[3] = (char*)malloc(sizeof(char) * 100);
	all->text.path[4] = (char*)malloc(sizeof(char) * 100);
	all->text.path[1] = NULL;
	all->text.path[0] = NULL;
	all->text.path[2] = NULL;
	all->text.path[3] = NULL;
	all->text.path[4] = NULL;
	init_color(&all->var.c_color);
	init_color(&all->var.f_color);
}

void			ft_exit(char *str)
{
	write(1, "Error\n", 6);
	write(1, str, ft_strlen(str));
	exit(0);
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
	if ((fd = open(file, O_DIRECTORY)) != -1)
		ft_exit("you've chosen an directory");
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit("wrong file");
	if ((all->var.line_breaks = count_line_breaks(all, fd)) == -1)
		ft_exit("something wrong with file");
	close(fd);
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit("wrong file");
	if (!((data = ft_calloc(all->var.line_breaks, sizeof(char*))) &&
		  (all->var.map = ft_calloc(all->var.line_breaks, sizeof(char*)))))
		ft_exit("malloc");
	while (get_next_line(fd, &data[i]) > 0)
		find_spec(data[i++], all);
	find_spec(data[i], all);
	close(fd);
	if (all->var.flag == 1.11111111)
		parser_map(all);
	else
		ft_exit("you've missed something or added too many things");
}

void			ft_free(t_all *all)
{
	all->text.path[0] = NULL;
	all->text.path[1] = NULL;
	all->text.path[2] = NULL;
	all->text.path[3] = NULL;
	all->text.path[4] = NULL;
	free(all->text.path[0]);
	free(all->text.path[1]);
	free(all->text.path[2]);
	free(all->text.path[3]);
	free(all->text.path[4]);
	all->text.path = NULL;
	free(all->text.path);
}