#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include "./get_next_line/get_next_line_bonus.h"
# include <unistd.h>

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct  s_data
{
	void        *mlx;
	void        *win;
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef struct s_texture
{
	void        **img;
	char        **addr;
	int         *bits_per_pixel;
	int         *line_length;
	int         *endian;
	int			*width;
	int 		*height;
	float 		coef;
	char		**path;
}				t_texture;

typedef struct		s_var
{
	t_color		f_color;
	t_color		c_color;
	int screen_width;
	int screen_height;
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	int map_x;
	int map_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	double perp_wall_dist;
	int step_x;
	int step_y;
	int hit;
	int side;
	int draw_start;
	int draw_end;
	double move_speed;
	double rot_speed;
	double old_dir_x;
	double old_plane_x;
	char **map;
	int line_height;
	int color;
	int tex_num;
	double wall_x;
	int tex_x;
	double step;
	double tex_pos;
	double tex_y;
	char *dst;
	char *src;
	double *zbuffer;
	unsigned int num_sprites;
	int *sprite_order;
	float *sprite_distance;
	double sprite_x;
	double sprite_y;
	double inv_det;
	double transfor_x;
	double transfor_y;
	int sprite_screen_x;
	int sprite_height;
	int draw_start_y;
	int draw_end_y;
	int sprite_width;
	int draw_start_x;
	int drawn_end_x;
	float **sprite;
	int stripe;
	int d;
	int			line_breaks;
	int			num_of_colum;
	double		flag;
	int			num_of_eof;
	int			num_of_char;



}					t_var;

typedef struct s_all
{

	t_data	mlx;
	t_var 	var;
	t_texture text;

}				t_all;

long int		ft_atoi(char *str);
void			set_player(t_all *all, char name);
int				ft_atoi_color(char *str);
char			*remove_space(char *data);
char			*remove_num(char *data);
void			parser_resolution(char *data, t_all *all);
char			*remove_comma(char *data);
void			parser_celling_color(char *data, t_all *all);
void			parser_floor_color(char *data, t_all *all);
char			*remove_name(char *data);
void			parser_path(char *data, t_all *all, int i);
void			parser_map(t_all *all);
void			find_spec(char *data, t_all *all);
void			ft_parser(char *file, t_all *all);
void			ft_exit(char *str);
int				check_value(const char *data);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
int				check_resolution(t_all *all);
int				check_n(const char *data);
int				check_xpm(const char *data);
int				check_data(const char *data);
int				check_first_line(t_all *all, int i, int j);
int				check_map_eof(t_all *all, int i);
int				check_player(t_all *all, int i);
int				check_sprite(t_all *all, int i);
int				check_last_line(t_all *all, int i);
int				check_from_top_to_bottom(t_all *all, int i);
void			check_inside_map(t_all *all, int i, int j);
void			check_in_map(t_all *all, int i);
int				check_first_row(t_all *all, int i);
void			check_all_map(t_all *all, int i);
int				ft_max(int x, int y);
void			make_map(t_all *all, char *data);
void			count_chars(char *data, t_all *all);
int				count_line_breaks(t_all *all, int fd);
void			init_color(t_color *color);
void			ft_init_parser(t_all *all);
void			ft_free(t_all *all);
int				ft_check_cub(const char *data);

#endif
