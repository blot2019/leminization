/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:00:33 by bgerda            #+#    #+#             */
/*   Updated: 2019/11/23 18:02:02 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "lemin.h"

void	upload_line(t_point *half, int x, int y)
{
	t_pix start;
	t_pix end;

	if (x < half->max_x - 1)
	{
		start = complect_t_pix(half, x, y);
		end = complect_t_pix(half, x + 1, y);
		charge_draw(&start, half);
		charge_draw(&end, half);
		drawline(start, end, half);
		//draw_circle(half, start.x, start.y, 5);
	}
	if (y < half->max_y - 1)
	{
		start = complect_t_pix(half, x, y);
		end = complect_t_pix(half, x, y + 1);
		charge_draw(&start, half);
		charge_draw(&end, half);
		drawline(start, end, half);
		//draw_circle(half, start.x, start.y, 5);
	}
}

void    upload_link(t_point *half, t_pix start, t_pix end)
{
	charge_draw(&end, half);
	drawline(start, end, half);
}

void    draw_start(t_point *half, t_pix start, int radius)
{
	start.color = 0xFFFFFF;
	while (--radius)
		draw_circle(half, start, radius);
}

void    draw_end(t_point *half, t_pix start, int radius)
{
	start.color = 0xFF00FF;
	while (--radius)
		draw_circle(half, start, radius);
}

int		draw_point(t_point *half)
{
//	int x;
//	int y;
//
//	y = 0;
//	while (half->axis[y])
//	{
//		x = 0;
//		while (half->axis[y][x])
//		{
//			upload_line(half, x, y);
//			x++;
//		}
//		y++;
//	}
	int i;
	t_links *list;
	t_pix start;
	t_pix end;
	int radius;

	i = -1;
	while (++i < half->lem->rooms_len)
	{
		radius = 10;
		list = half->lem->rooms[i].links;
		start = complect_t_pix(half, half->lem->rooms[i].x_coord, half->lem->rooms[i].y_coord);
		charge_draw(&start, half);
		while(list)
		{
			end = complect_t_pix(half, list->link->x_coord, list->link->y_coord);
			upload_link(half, start, end);
			list = list->next;
		}
		draw_circle(half, start, radius);
		mlx_string_put(half->mlx_ptr, half->window, start.x, start.y, 0xFFFFFF, half->lem->rooms[i].name);
		if (half->lem->rooms[i].part > 0)
			draw_start(half, start, radius);
		if (half->lem->rooms[i].part < 0)
			draw_end(half, start, radius);

	}
	return (0);
}
int		draw_text(t_point *half)
{
	int i;
	t_pix start;

	i = -1;
	while (++i < half->lem->rooms_len)
	{
		start = complect_t_pix(half, half->lem->rooms[i].x_coord, half->lem->rooms[i].y_coord);
		charge_draw(&start, half);
		mlx_string_put(half->mlx_ptr, half->window, start.x - 10, start.y + 5, 0xFFFFFF, half->lem->rooms[i].name);

	}
	return (0);
}
void	open_window(t_point *half)
{
	draw_point(half);
	mlx_put_image_to_window(half->mlx_ptr, half->window, half->map, 0, 0);
	draw_text(half);
	set_hooks(half);
	mlx_loop(half->mlx_ptr);
}

int		main(int ac, char **av)
{
	t_point half;
	t_lemin lemin;

	if (!lets_read(&lemin))
		return (err_out());
	zero_to_half(&half, &lemin);
	half.lem = &lemin;
	open_window(&half);
	return (0);
}
