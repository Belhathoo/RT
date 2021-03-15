/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:31:11 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/11 12:31:26 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void			*rt_run(t_thread *t)
{
	t_vec		c;
	int			color;
	int			col;
	int			row;

	row = IMG_HEIGHT + 1;
	while (--row >= 0)
	{
		col = (int)(t->i * IMG_WIDTH / NBTHREAD) - 1;
		while (++col < (int)((t->i + 1) * IMG_WIDTH / NBTHREAD))
		{
			c = rt_anti_aliasing(t, col, row);
			color = rt_rgb_to_int(c);
			rt_mlx_putpixel(t->rt, col, IMG_HEIGHT - row, color);
		}
	}
	pthread_exit(NULL);
}

void			*rt_run_50(t_thread *t)
{
	t_vec		c;
	int			color;
	int			col;
	int			row;

	row = IMG_HEIGHT + 1;
	while (--row >= 0)
	{
		col = (int)(t->i * IMG_WIDTH / NBTHREAD) - 1;
		while (++col < (int)((t->i + 1) * IMG_WIDTH / NBTHREAD))
		{
			c = rt_anti_aliasing(t, col, row);
			color = rt_rgb_to_int(c);
			rt_mlx_putpixel(t->rt, col, IMG_HEIGHT - row, color);
			rt_mlx_putpixel(t->rt, col + 1, IMG_HEIGHT - row, color);
			col++;
		}
	}
	pthread_exit(NULL);
}

void			*rt_run_25(t_thread *t)
{
	t_vec		c;
	int			color;
	int			col;
	int			row;

	row = IMG_HEIGHT + 1;
	while (--row >= 0)
	{
		col = (int)(t->i * IMG_WIDTH / NBTHREAD) - 1;
		while (++col < (int)((t->i + 1) * IMG_WIDTH / NBTHREAD))
		{
			c = rt_anti_aliasing(t, col, row);
			color = rt_rgb_to_int(c);
			rt_mlx_putpixel(t->rt, col, IMG_HEIGHT - row, color);
			rt_mlx_putpixel(t->rt, col + 1, IMG_HEIGHT - row, color);
			rt_mlx_putpixel(t->rt, col, IMG_HEIGHT - row - 1, color);
			rt_mlx_putpixel(t->rt, col + 1, IMG_HEIGHT - row - 1, color);
			col++;
		}
		row--;
	}
	pthread_exit(NULL);
}

void			*rt_run_12(t_thread *t)
{
	int			color;
	int			col;
	int			row;

	row = IMG_HEIGHT + 1;
	while (--row >= 0)
	{
		col = (int)(t->i * IMG_WIDTH / NBTHREAD) - 1;
		while (++col < (int)((t->i + 1) * IMG_WIDTH / NBTHREAD))
		{
			color = rt_rgb_to_int(rt_anti_aliasing(t, col, row));
			rt_mlx_putpixel(t->rt, col, IMG_HEIGHT - row, color);
			rt_mlx_putpixel(t->rt, col + 1, IMG_HEIGHT - row, color);
			rt_mlx_putpixel(t->rt, col + 2, IMG_HEIGHT - row, color);
			rt_mlx_putpixel(t->rt, col, IMG_HEIGHT - row - 1, color);
			rt_mlx_putpixel(t->rt, col + 1, IMG_HEIGHT - row - 1, color);
			rt_mlx_putpixel(t->rt, col + 2, IMG_HEIGHT - row - 1, color);
			rt_mlx_putpixel(t->rt, col, IMG_HEIGHT - row - 2, color);
			rt_mlx_putpixel(t->rt, col + 1, IMG_HEIGHT - row - 2, color);
			rt_mlx_putpixel(t->rt, col + 2, IMG_HEIGHT - row - 2, color);
			col += 2;
		}
		row -= 2;
	}
	pthread_exit(NULL);
}
