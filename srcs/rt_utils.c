/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:39:58 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/15 18:40:21 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void			my_mlx_putpixel(t_vec *data, int x, int y, t_vec color)
{
	if (x >= 0 && x < IMG_WIDTH && y >= 0 && y < IMG_HEIGHT)
		data[y * (int)IMG_WIDTH + x] = color;
}

t_vec			my_mlx_getpixel(t_vec *data, int x, int y)
{
	if (x >= 0 && x < IMG_WIDTH && y >= 0 && y < IMG_HEIGHT)
		return (data[y * (int)IMG_WIDTH + x]);
	return ((t_vec){0, 0, 0});
}

double			ffmax(double a, double b)
{
	return (a > b ? a : b);
}

void			ft_float_swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
