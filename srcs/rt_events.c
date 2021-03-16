/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 10:55:11 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/11 16:13:45 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		rt_reset(t_rt *rt)
{
	t_object *o;

	rt->scene->progress = 1;
	rt->scene->select = 0;
	o = rt->scene->sl_obj;
	if (rt->scene->key_cam == 1)
		rt->scene->cam = rt_init_camera(rt->scene->cam.lookfrom,
				rt->scene->cam.lookat, rt->scene->cam.fov);
	else if (o && o->compos)
	{
		rt_free_compos(o);
		get_cube_compos(o, rt);
	}
	rt->scene->key = 1;
}

int			rt_keys(int key, t_rt *rt)
{
	if (key == K_ESC)
		rt_close(rt);
	if (key == K_S)
		save_btn(rt);
	if (rt->scene->dyn && key == K_L)
		light_btn(rt);
	if (rt->scene->key_mvt == 1)
	{
		if (rt->scene->key_cam == 1)
			(rt_move(key, &rt->scene->cam.lookfrom)) ? rt_reset(rt) : 0;
		else if (rt->scene->sl_obj != NULL)
		{
			if (rt_move(key, &rt->scene->sl_obj->pos)\
					&& rt_move(key, &rt->scene->sl_obj->sl_pnt))
				rt_reset(rt);
			if (rt_rot_event(key, rt->scene->sl_obj))
				rt_reset(rt);
		}
	}
	return (0);
}
