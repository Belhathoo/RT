/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_btns_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:11:30 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/14 16:11:32 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		square_fill(t_rt *data, int color, t_vec pos, t_vec size)
{
	int		i;
	int		j;

	i = (int)pos.x - 1;
	while (++i < (int)size.x)
	{
		j = pos.y - 1;
		while (++j < size.y)
			mlx_pixel_put(data->mlx, data->win, i, j, color);
	}
}

void		square_str(t_rt *data, char *str, t_vec pos, t_vec size)
{
	t_vec	t;

	t.x = pos.x;
	t.y = pos.y;
	mlx_string_put(data->mlx, data->win, t.x, t.y, 0x000000, str);
}

void		ctrl_name(t_rt *data)
{
	square_fill(data, 0xFFFFFF, (t_vec){700, 10, 0}, (t_vec){900, 50, 0});
	square_str(data, data->scene->sl_obj->name,
					(t_vec){700, 10, 0}, (t_vec){900, 50, 0});
}
