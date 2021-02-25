#include "cub3d.h"

void	sprite_count(t_all *all, unsigned int k)
{
	all->var.sprite_x = all->sprite[k].x - all->var.pos_x + 0.5;
	all->var.sprite_y = all->sprite[k].y - all->var.pos_y + 0.5;
	all->var.inv_det = 1.0 / (all->var.plane_x * all->var.dir_y -
	all->var.dir_x * all->var.plane_y);
	all->var.transfor_x = all->var.inv_det * (all->var.dir_y *
	all->var.sprite_x - all->var.dir_x * all->var.sprite_y);
	all->var.transfor_y = all->var.inv_det * (-all->var.plane_y *
	all->var.sprite_x + all->var.plane_x * all->var.sprite_y);
	all->var.sprite_screen_x = (int)((all->var.screen_width / 2) *
	(1 + all->var.transfor_x / all->var.transfor_y));
	all->var.sprite_height = abs((int)(all->var.screen_height /
	all->var.transfor_y));
	all->var.draw_start_y = -all->var.sprite_height / 2 +
	all->var.screen_height / 2;
	if (all->var.draw_start_y < 0)
		all->var.draw_start_y = 0;
	all->var.draw_end_y = all->var.sprite_height / 2 +
	all->var.screen_height / 2;
	if (all->var.draw_end_y >= all->var.screen_height)
		all->var.draw_end_y = all->var.screen_height - 1;
	all->var.sprite_width = abs((int)(all->var.screen_height /
	all->var.transfor_y));
}

void	sprite_count_draw(t_all *all)
{
	all->var.draw_start_x = -1 * all->var.sprite_width / 2 +
	all->var.sprite_screen_x;
	if (all->var.draw_start_x < 0)
		all->var.draw_start_x = 0;
	all->var.drawn_end_x = all->var.sprite_width / 2 +
	all->var.sprite_screen_x;
	if (all->var.drawn_end_x >= all->var.screen_width)
		all->var.drawn_end_x = all->var.screen_width - 1;
	all->var.stripe = all->var.draw_start_x;
}

void	sprite_draw(t_all *all)
{
	int y;

	all->var.tex_x = (int)(256 * (all->var.stripe - (-all->var.sprite_width / 2
			+ all->var.sprite_screen_x)) * all->text.width[4] /
					all->var.sprite_width) / 256;
	y = all->var.draw_start_y;
	if (all->var.transfor_y > 0 && all->var.stripe > 0 && all->var.stripe <
	all->var.screen_width && all->var.transfor_y <
	all->var.zbuffer[all->var.stripe])
	{
		while (y < all->var.draw_end_y - 1)
		{
			all->var.d = y * 256 - all->var.screen_height * 128 +
					all->var.sprite_height * 128;
			all->var.tex_y = (((all->var.d) * all->text.height[4]) /
			all->var.sprite_height) / 256;
			all->var.color = text_pix_color(all, all->var.tex_x,
											(int) all->var.tex_y);
			if ((all->var.color & 0x00FFFFFF))
				my_mlx_pixel_put(all, all->var.stripe, y, all->var.color);
			y++;
		}
	}
}
