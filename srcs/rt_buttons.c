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
	// swap_button_by_id(SAVE_BTN , rt);
	image_create(rt);  
}

void        cam_btn(t_rt *rt)
{
	RS->key_cam = (RS->key_cam + 1) % 2;
	swap_button_by_id(CAM_BTN, rt);
}

void            mvt_btn(t_rt *rt)
{
	swap_button_by_id(MVT_BTN , rt);
	RS->sl_obj = NULL; // rmve for mac
	RS->key_mvt = (RS->key_mvt + 1) % 2;
	if (!RS->key_mvt && RS->key_cam == 1)
		swap_button_by_id(CAM_BTN, rt);
	RS->key_cam = 0;
	RS->key = 1;
	rt_reset(rt);
}

void        light_btn(t_rt *rt)
{
	ft_putstr("LOLO");
	if (RS->light)
		RS->light = NULL;
	else if (rt->s_light)
		RS->light = rt->s_light;
	else
		return ;
	swap_button_by_id(LGHT_BTN , rt);
	rt_reset(rt);
}

void        dame_btn(t_rt *rt)
{
	if (RS->sl_obj->txt.is_txt == 0)
	{
		if (RS->sl_obj->noi.is_noise == 0)
		{
			RS->sl_obj->noi.is_noise = 1;
			RS->sl_obj->noi.type = DAMIER;
			RS->sl_obj->scale = 14;
		}
		else if (RS->sl_obj->noi.type == DAMIER)
			RS->sl_obj->noi.is_noise = 0; // scale!
		else
		{
			RS->sl_obj->scale = 14;
			RS->sl_obj->noi.type = DAMIER;
		}
		rt_reset(rt); //--
	}
}


void        circ_btn(t_rt *rt)
{
	if (RS->sl_obj->txt.is_txt == 0)
	{
		if (RS->sl_obj->noi.is_noise == 0)
		{
			RS->sl_obj->noi.is_noise = 1;
			RS->sl_obj->noi.type = CIRCLES;
			RS->sl_obj->scale = 10;
		}
		else if (RS->sl_obj->noi.type == CIRCLES)
			RS->sl_obj->noi.is_noise = 0; // scale!
		else
		{
			RS->sl_obj->scale = 10;
			RS->sl_obj->noi.type = CIRCLES;
		}
		rt_reset(rt); //--
	}
}

void        v1_btn(t_rt *rt)
{
	if (RS->sl_obj->txt.is_txt == 0)
	{
		if (RS->sl_obj->noi.is_noise == 0)
		{
			RS->sl_obj->noi.is_noise = 1;
			RS->sl_obj->noi.type = VORONOI1;
			RS->sl_obj->scale = 4;
		}
		else if (RS->sl_obj->noi.type == VORONOI1)
			RS->sl_obj->noi.is_noise = 0; // scale!
		else
		{
			RS->sl_obj->scale = 4;
			RS->sl_obj->noi.type = VORONOI1;
		}
		rt_reset(rt); //--
	}
}

void        v2_btn(t_rt *rt)
{
	if (RS->sl_obj->txt.is_txt == 0)
	{
		if (RS->sl_obj->noi.is_noise == 0)
		{
			RS->sl_obj->noi.is_noise = 1;
			RS->sl_obj->noi.type = VORONOI2;
			RS->sl_obj->scale = 2.0;
		}
		else if (RS->sl_obj->noi.type == VORONOI2)
			RS->sl_obj->noi.is_noise = 0; // scale!
		else
		{
			RS->sl_obj->scale = 2.0;
			RS->sl_obj->noi.type = VORONOI2;
		}
		rt_reset(rt); //--
	}
}


void        v3_btn(t_rt *rt)
{
	if (RS->sl_obj->txt.is_txt == 0)
	{
		if (RS->sl_obj->noi.is_noise == 0)
		{
			RS->sl_obj->noi.is_noise = 1;
			RS->sl_obj->noi.type = VORONOI3;
			RS->sl_obj->scale = 0.1;
		}
		else if (RS->sl_obj->noi.type == VORONOI3)
			RS->sl_obj->noi.is_noise = 0; // scale!
		else
		{
			RS->sl_obj->scale = 0.1;
			RS->sl_obj->noi.type = VORONOI3;
		}
		rt_reset(rt); //--
	}
}