/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 23:48:34 by belhatho          #+#    #+#             */
/*   Updated: 2020/12/28 16:28:59 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			ft_mlx_putpixel(t_ptr *p, int x, int y, int color)
{
	if (x >= 0 && x < IMG_WIDTH && y >= 0 && y < IMG_HEIGHT)
		p->data[y * (int)IMG_WIDTH + x] = color;
}

t_vec			ft_calcul(t_thread *th, t_ray ray)
{
	t_vec		col;

	col = ft_vec(0, 0, 0);
	if (ft_hit(th->p->scene->obj, ray, &th->rec, DBL_MAX) > 0)
		ft_lighting(th, th->p->scene->light, &col);
	return (col);
}

int				ft_anti_a(t_thread *th, double i, double j)
{
	t_vec		col;
	t_ray		r;
	double		ss[2];
	int			anti_a;

	col = ft_vec(0, 0, 0);
	ss[0] = -1;
	anti_a = th->p->scene->anti_a;
	while (++ss[0] < anti_a)
	{
		ss[1] = -1;
		while (++ss[1] < anti_a)
		{
			r = ft_ray_tracer(th->p, i + ((ss[0] + 0.5) / anti_a), j + ((ss[1] + 0.5) / anti_a));
			col = ft_plus(col, ft_calcul(th, r));
		}
	}
	col = ft_div_k(col, anti_a * anti_a);
	ft_clamp(&col);
	return (ft_rgb_to_int(col));
}

void			*ft_draw(t_thread *thread)
{
	double		i;
	double		j;
	int			c;

	j = IMG_HEIGHT;
	while (--j >= 0)
	{
		i = (int)(thread->i * IMG_WIDTH / NBTHREAD) - 1;
		while (++i < (int)((thread->i + 1) * IMG_WIDTH / NBTHREAD))
		{
			c = ft_anti_a(thread, i, j);
			ft_mlx_putpixel(thread->p, i, IMG_HEIGHT - j, c);
		}
	}
	pthread_exit(NULL);
}

void			kick_off(t_ptr *p)
{
	pthread_t	thread[NBTHREAD];
	t_thread	div[NBTHREAD];
	int			i;

	ft_bzero(p->data, IMG_WIDTH * IMG_HEIGHT * 4);
	i = -1;
	while (++i < NBTHREAD)
	{
		div[i].i = i;
		div[i].p = p;
		pthread_create(&thread[i], NULL, (void*)ft_draw, &div[i]);
	}
	while (--i >= 0)
		pthread_join(thread[i], NULL);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
}
