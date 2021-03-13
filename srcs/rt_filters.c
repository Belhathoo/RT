/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_filters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:40:58 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/13 16:41:00 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static int		sepia(t_vec c)
{
	t_vec		v;

	v.x = ft_clamping(((c.x * .393) + (c.y * .769) + (c.z * .189) / 255.99));
	v.y = ft_clamping(((c.x * .349) + (c.y * .686) + (c.z * .168) / 255.99));
	v.z = ft_clamping(((c.x * .272) + (c.y * .534) + (c.z * .131) / 255.99));
	return (rt_rgb_to_int(v));
}

void			rt_sepia_filter(int *data)
{
	int i;

	i = 0;
	while (i < (IMG_WIDTH * IMG_HEIGHT))
	{
		data[i] = sepia(rt_int_to_rgb(data[i]));
		i++;
	}
}

void			rt_filter_gray(int *data)
{
	int		i;
	t_vec	c;

	i = 0;
	while (i < (IMG_WIDTH * IMG_HEIGHT))
	{
		c = rt_int_to_rgb(data[i]);
		data[i] = rt_rgb_to_int(vec3(ft_maxd3(c.x, c.y, c.z)));
		i++;
	}
}

void			rt_filter_neg(int *data)
{
	int i;

	i = 0;
	while (i < (IMG_WIDTH * IMG_HEIGHT))
	{
		data[i] = rt_rgb_to_int(vec_sub(vec3(1.0), rt_int_to_rgb(data[i])));
		i++;
	}
}
