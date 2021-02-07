#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>

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
	char		*path;

}				t_texture;

typedef struct		s_var
{
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
	int map[24][24];
	int line_height;
	int color;
	int tex_num;
	double wall_x;
	double tex_x;
	int tex_width;
	int tex_height;
	double step;
	double tex_pos;
	int tex_y;
	char *dst;
	char *src;
	int i;


}					t_var;

typedef struct s_all
{

	t_data	mlx;
	t_var 	var;
	t_texture text;

}				t_all;

#endif
