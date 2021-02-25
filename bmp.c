#include "cub3d.h"

void	create_header(t_all *all, int fd)
{
	char	tmp[14];
	int		size;

	size = 54 + (all->var.screen_height * all->var.screen_width *
			all->mlx.bits_per_pixel / 8);
	ft_bzero(tmp, 14);
	tmp[0] = 'B';
	tmp[1] = 'M';
	tmp[2] = (unsigned char)size;
	tmp[3] = (unsigned char)(size >> 8);
	tmp[4] = (unsigned char)(size >> 16);
	tmp[5] = (unsigned char)(size >> 24);
	tmp[10] = 54;
	write(fd, &tmp, 14);
}

void	create_bmp_inside(t_all *all, int fd)
{
	char tmp[40];

	ft_bzero(tmp, 40);
	tmp[0] = 40;
	tmp[4] = (unsigned char)all->var.screen_width;
	tmp[5] = (unsigned char)(all->var.screen_width >> 8);
	tmp[6] = (unsigned char)(all->var.screen_width >> 16);
	tmp[7] = (unsigned char)(all->var.screen_width >> 24);
	tmp[8] = (unsigned char)all->var.screen_height;
	tmp[9] = (unsigned char)(all->var.screen_height >> 8);
	tmp[10] = (unsigned char)(all->var.screen_height >> 16);
	tmp[11] = (unsigned char)(all->var.screen_height >> 24);
	tmp[12] = (unsigned char)1;
	tmp[14] = (unsigned char)(all->mlx.bits_per_pixel);
	write(fd, &tmp, 40);
}

void	create_bmp(t_all *all)
{
	char	*str;
	int		fd;
	int		height;

	height = all->var.screen_height;
	str = all->mlx.addr;
	if (!(fd = open("pic.bmp", O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644)))
		ft_exit("can't create bmp file", all);
	create_header(all, fd);
	create_bmp_inside(all, fd);
	while (--height)
		str += all->mlx.line_length;
	while (height < all->var.screen_height)
	{
		write(fd, str, all->var.screen_width * 4);
		str -= all->mlx.line_length;
		height++;
	}
	close(fd);
	ft_close(all);
}

int		check_save(char *data)
{
	int i;

	i = 0;
	while (data[i] != '\0')
		i++;
	i--;
	if (data[i] == 'e' && data[i - 1] == 'v' && data[i - 2] == 'a' &&
		data[i - 3] == 's' && data[i - 4] == '-' && data[i - 5] == '-' &&
		i >= 5)
		return (1);
	return (-1);
}
