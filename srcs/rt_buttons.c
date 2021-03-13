/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_buttons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:56:46 by msoulaim          #+#    #+#             */
/*   Updated: 2021/03/06 19:11:26 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void        save_btn(t_rt *rt)
{
	image_create(rt);  
}

void        cam_btn(t_rt *rt)
{
	rt->scene->key_cam = (rt->scene->key_cam + 1) % 2;
	swap_button_by_id(CAM_BTN, rt);
}

void            mvt_btn(t_rt *rt)
{
	swap_button_by_id(MVT_BTN , rt);
	rt->scene->sl_obj = NULL; // rmve for mac
	rt->scene->key_mvt = (rt->scene->key_mvt + 1) % 2;
	if (!rt->scene->key_mvt && rt->scene->key_cam == 1)
		swap_button_by_id(CAM_BTN, rt);
	rt->scene->key_cam = 0;
	rt->scene->key = 1;
	rt_reset(rt);
}

void        light_btn(t_rt *rt)
{
	if (rt->scene->light)
		rt->scene->light = NULL;
	else if (rt->s_light)
		rt->scene->light = rt->s_light;
	else
		return ;
	swap_button_by_id(LGHT_BTN , rt);
	rt_reset(rt);
}

void        dame_btn(t_rt *rt)
{
	if (rt->scene->sl_obj->txt.is_txt == 0)
	{
		if (rt->scene->sl_obj->noi.is_noise == 0)
		{
			rt->scene->sl_obj->noi.is_noise = 1;
			rt->scene->sl_obj->noi.type = DAMIER;
			rt->scene->sl_obj->scale = 14;
		}
		else if (rt->scene->sl_obj->noi.type == DAMIER)
			rt->scene->sl_obj->noi.is_noise = 0; // scale!
		else
		{
			rt->scene->sl_obj->scale = 14;
			rt->scene->sl_obj->noi.type = DAMIER;
		}
		rt_reset(rt); //--
	}
}


void        circ_btn(t_rt *rt)
{
	if (rt->scene->sl_obj->txt.is_txt == 0)
	{
		if (rt->scene->sl_obj->noi.is_noise == 0)
		{
			rt->scene->sl_obj->noi.is_noise = 1;
			rt->scene->sl_obj->noi.type = CIRCLES;
			rt->scene->sl_obj->scale = 10;
		}
		else if (rt->scene->sl_obj->noi.type == CIRCLES)
			rt->scene->sl_obj->noi.is_noise = 0; // scale!
		else
		{
			rt->scene->sl_obj->scale = 10;
			rt->scene->sl_obj->noi.type = CIRCLES;
		}
		rt_reset(rt); //--
	}
}

void        v1_btn(t_rt *rt)
{
	if (rt->scene->sl_obj->txt.is_txt == 0)
	{
		if (rt->scene->sl_obj->noi.is_noise == 0)
		{
			rt->scene->sl_obj->noi.is_noise = 1;
			rt->scene->sl_obj->noi.type = VORONOI1;
			rt->scene->sl_obj->scale = 4;
		}
		else if (rt->scene->sl_obj->noi.type == VORONOI1)
			rt->scene->sl_obj->noi.is_noise = 0; // scale!
		else
		{
			rt->scene->sl_obj->scale = 4;
			rt->scene->sl_obj->noi.type = VORONOI1;
		}
		rt_reset(rt); //--
	}
}

void        v2_btn(t_rt *rt)
{
	if (rt->scene->sl_obj->txt.is_txt == 0)
	{
		if (rt->scene->sl_obj->noi.is_noise == 0)
		{
			rt->scene->sl_obj->noi.is_noise = 1;
			rt->scene->sl_obj->noi.type = VORONOI2;
			rt->scene->sl_obj->scale = 2.0;
		}
		else if (rt->scene->sl_obj->noi.type == VORONOI2)
			rt->scene->sl_obj->noi.is_noise = 0; // scale!
		else
		{
			rt->scene->sl_obj->scale = 2.0;
			rt->scene->sl_obj->noi.type = VORONOI2;
		}
		rt_reset(rt); //--
	}
}


void        v3_btn(t_rt *rt)
{
	if (rt->scene->sl_obj->txt.is_txt == 0)
	{
		if (rt->scene->sl_obj->noi.is_noise == 0)
		{
			rt->scene->sl_obj->noi.is_noise = 1;
			rt->scene->sl_obj->noi.type = VORONOI3;
			rt->scene->sl_obj->scale = 0.1;
		}
		else if (rt->scene->sl_obj->noi.type == VORONOI3)
			rt->scene->sl_obj->noi.is_noise = 0; // scale!
		else
		{
			rt->scene->sl_obj->scale = 0.1;
			rt->scene->sl_obj->noi.type = VORONOI3;
		}
		rt_reset(rt); //--
	}
}