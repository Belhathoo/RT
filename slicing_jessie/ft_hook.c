/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 01:47:03 by belhatho          #+#    #+#             */
/*   Updated: 2021/01/31 15:10:20 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_close(t_ptr *p)
{
	image_create((int *)p->data);
	mlx_destroy_image(p->mlx, p->img);
	mlx_destroy_window(p->mlx, p->win);
	ft_fexit(0, 0, &p);
	return (0);
}

int			ft_deal_key(int key, t_ptr *p)
{
	if (key == MLX_KEY_ESC)
		ft_close(p);
	return (key);
}

void		ft_clamp(t_vec *c)
{
	c->e1 = ft_clamping(c->e1);
	c->e2 = ft_clamping(c->e2);
	c->e3 = ft_clamping(c->e3);
}

double		ft_clamping(double value)
{
	if (value < 0.0)
		value = 0.0;
	if (value > 1.0)
		value = 1.0;
	return (value);
}

int			ft_rgb_to_int(t_vec c)
{
	int r;
	int g;
	int b;

	r = (int)(255.99 * c.e1);
	g = (int)(255.99 * c.e2);
	b = (int)(255.99 * c.e3);
	return (r * 256 * 256 + g * 256 + b);
}
