/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_buttons_ann.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:21:37 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/15 17:21:40 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	dame_btn(t_rt *rt)
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
			rt->scene->sl_obj->noi.is_noise = 0;
		else
		{
			rt->scene->sl_obj->scale = 14;
			rt->scene->sl_obj->noi.type = DAMIER;
		}
		rt_reset(rt);
	}
}

void	circ_btn(t_rt *rt)
{
	if (rt->scene->sl_obj->txt.is_txt == 0)
	{
		if (rt->scene->sl_obj->noi.is_noise == 0)
		{
			rt->scene->sl_obj->noi.is_noise = 1;
			rt->scene->sl_obj->noi.type = CIRCLES;
			rt->scene->sl_obj->scale = 5;
		}
		else if (rt->scene->sl_obj->noi.type == CIRCLES)
			rt->scene->sl_obj->noi.is_noise = 0;
		else
		{
			rt->scene->sl_obj->scale = 5;
			rt->scene->sl_obj->noi.type = CIRCLES;
		}
		rt_reset(rt);
	}
}

void	v1_btn(t_rt *rt)
{
	if (rt->scene->sl_obj->txt.is_txt == 0)
	{
		if (rt->scene->sl_obj->noi.is_noise == 0)
		{
			rt->scene->sl_obj->noi.is_noise = 1;
			rt->scene->sl_obj->noi.type = VORONOI1;
			rt->scene->sl_obj->scale = 1;
		}
		else if (rt->scene->sl_obj->noi.type == VORONOI1)
			rt->scene->sl_obj->noi.is_noise = 0;
		else
		{
			rt->scene->sl_obj->scale = 1;
			rt->scene->sl_obj->noi.type = VORONOI1;
		}
		rt_reset(rt);
	}
}

void	v2_btn(t_rt *rt)
{
	if (rt->scene->sl_obj->txt.is_txt == 0)
	{
		if (rt->scene->sl_obj->noi.is_noise == 0)
		{
			rt->scene->sl_obj->noi.is_noise = 1;
			rt->scene->sl_obj->noi.type = VORONOI2;
			rt->scene->sl_obj->scale = 1;
		}
		else if (rt->scene->sl_obj->noi.type == VORONOI2)
			rt->scene->sl_obj->noi.is_noise = 0;
		else
		{
			rt->scene->sl_obj->scale = 1.0;
			rt->scene->sl_obj->noi.type = VORONOI2;
		}
		rt_reset(rt);
	}
}

void	v3_btn(t_rt *rt)
{
	if (rt->scene->sl_obj->txt.is_txt == 0)
	{
		if (rt->scene->sl_obj->noi.is_noise == 0)
		{
			rt->scene->sl_obj->noi.is_noise = 1;
			rt->scene->sl_obj->noi.type = VORONOI3;
			rt->scene->sl_obj->scale = 1;
		}
		else if (rt->scene->sl_obj->noi.type == VORONOI3)
			rt->scene->sl_obj->noi.is_noise = 0;
		else
		{
			rt->scene->sl_obj->scale = 1;
			rt->scene->sl_obj->noi.type = VORONOI3;
		}
		rt_reset(rt);
	}
}
