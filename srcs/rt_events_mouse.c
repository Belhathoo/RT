/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_events_mouse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:13:57 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/15 15:27:59 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void			rt_select_obj(t_rt *rt, int col, int row)
{
	t_ray		r;
	t_hit		rec;

	r = rt_get_ray(&rt->scene->cam, (double)(col + 0.5) / IMG_WIDTH,
			(double)(row + 0.5) / IMG_HEIGHT);
	if (rt_hit(rt->scene, &r, &rec, MAX))
	{
		rt->scene->sl_obj = rec.curr_obj;
		ft_putstr(" - selected obj: ");
		ft_putendl(rt->scene->sl_obj->name);
	}
	else
		rt->scene->sl_obj = NULL;
}

void			rt_mouse_btn(int btn, t_rt *rt)
{
	(btn == LGHT_BTN) ? light_btn(rt) : 0;
	if (btn == CAM_BTN)
		cam_btn(rt);
	else if (rt->scene->sl_obj != NULL)
	{
		(btn == DAME_BTN) ? dame_btn(rt) : 0;
		(btn == CIRC_BTN) ? circ_btn(rt) : 0;
		(btn == V1_BTN) ? v1_btn(rt) : 0;
		(btn == V2_BTN) ? v2_btn(rt) : 0;
		(btn == V3_BTN) ? v3_btn(rt) : 0;
	}
}

int				rt_mouse(int button, int x, int y, t_rt *rt)
{
	int		btn;

	btn = 0;
	btn = get_selected_button(x, y, rt);
	(btn == SAVE_BTN) ? save_btn(rt) : 0;
	(rt->scene->dyn && btn == LGHT_BTN) ? light_btn(rt) : 0;
	if (!rt->scene->dyn)
	{
		if (button == 2)
			rt->scene->sl_obj = NULL;
		if (button == 1 &&
				((x > FRAME_LFT && x < IMG_WIDTH + FRAME_RGHT)\
				&& y > FRAME_DWN && y < IMG_HEIGHT + FRAME_UP))
			rt_select_obj(rt, x - FRAME_LFT, (int)IMG_HEIGHT - (y - FRAME_UP));
		if (btn != -1)
		{
			(btn == MVT_BTN) ? mvt_btn(rt) : 0;
			(rt->scene->key_mvt == 1) ? rt_mouse_btn(btn, rt) : 0;
			return (0);
		}
	}
	return (0);
}
