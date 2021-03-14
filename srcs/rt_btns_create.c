/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_btns_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:10:30 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/13 19:14:48 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		swap_void(void **dflt, void **img)
{
	void *p;

	p = *dflt;
	*dflt = *img;
	*img = p;
}

void		swap_button_by_id(int id, t_rt *rt)
{
	swap_void(&rt->bt[id]->deflt, &rt->bt[id]->img);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->bt[id]->deflt,
				(int)rt->bt[id]->pos.x, (int)rt->bt[id]->pos.y);
}

void		create_buttons(int size, t_rt *rt)
{
	t_button **b;

	rt->btns_up = vec(10, 100, 0);
	rt->btns_noi = vec(25, 470, 0);
	b = (t_button **)malloc(size * sizeof(t_button *));
	b[SAVE_BTN] = save_button(rt);
	b[MVT_BTN] = mvmnt_button(rt);
	b[CAM_BTN] = cam_button(rt);
	b[LGHT_BTN] = light_button(rt);
	b[DAME_BTN] = damier_button(rt);
	b[CIRC_BTN] = circles_button(rt);
	b[V1_BTN] = voronoi1_button(rt);
	b[V2_BTN] = voronoi2_button(rt);
	b[V3_BTN] = voronoi3_button(rt);
	rt->bt = b;
	rt->size_bt = size;
}

int			get_selected_button(int x, int y, t_rt *rt)
{
	int i;

	i = 0;
	while (i < rt->size_bt)
	{
		if ((((int)rt->bt[i]->pos.x <= x) &&
		(x <= (int)rt->bt[i]->pos.x + rt->bt[i]->w))
		&& (((int)rt->bt[i]->pos.y <= y) &&
		(y <= (int)rt->bt[i]->pos.y + rt->bt[i]->h)))
			return (i);
		i++;
	}
	return (-1);
}

void		free_buttons(t_rt *rt)
{
	int i;

	i = 0;
	while (i < rt->size_bt && rt->bt[i])
	{
		(rt->bt[i]) ? free(rt->bt[i]) : 0;
		i++;
	}
	rt->bt ? free(rt->bt) : 0;
}
