/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_buttons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:56:46 by msoulaim          #+#    #+#             */
/*   Updated: 2021/03/13 18:51:38 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	save_btn(t_rt *rt)
{
	image_create(rt);
}

void	cam_btn(t_rt *rt)
{
	rt->scene->key_cam = (rt->scene->key_cam + 1) % 2;
	swap_button_by_id(CAM_BTN, rt);
}

void	mvt_btn(t_rt *rt)
{
	swap_button_by_id(MVT_BTN, rt);
	rt->scene->key_mvt = (rt->scene->key_mvt + 1) % 2;
	if (!rt->scene->key_mvt && rt->scene->key_cam == 1)
		swap_button_by_id(CAM_BTN, rt);
	rt->scene->key_cam = 0;
	rt->scene->key = 1;
	rt_reset(rt);
}

void	light_btn(t_rt *rt)
{
	if (rt->scene->light)
		rt->scene->light = NULL;
	else if (rt->s_light)
		rt->scene->light = rt->s_light;
	else
		return ;
	swap_button_by_id(LGHT_BTN, rt);
	rt_reset(rt);
}
