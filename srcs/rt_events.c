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
	RS->progress = 1;
	RS->select = 0;
	if (RS->key_cam == 1)
	{
		RS->cam = rt_init_camera(RS->cam.lookfrom,
				RS->cam.lookat, RS->cam.fov);
	}
	else if (RS->sl_obj)
	{
		if (RS->sl_obj->compos)
			get_cube_compos(RS->sl_obj, rt);
	}
	RS->key = 1;
}

int			rt_keys(int key, t_rt *rt)
{
	//rt selt obj in main.c !!!! for linux events
	// (RS->sl_obj) ? ft_putendl(RS->sl_obj->name) : 0;
	if (key == K_ESC)
		rt_close(rt);
	if (key == K_A)
		mvt_btn(rt);
	if (key == K_S)
		save_btn(rt);
	if (RS->key_mvt == 1)
	{ //
		if (key == K_C)
			cam_btn(rt);
		else if (key == K_L)
			light_btn(rt);
	}//
	if (RS->key_mvt == 1)
	{
		if (RS->key_cam == 1)
			(rt_move(key, &RS->cam.lookfrom)) ? rt_reset(rt) : 0;
		else if (RS->sl_obj != NULL)
		{
			if (rt_move(key, &RS->sl_obj->pos)\
			&& rt_move(key, &RS->sl_obj->sl_pnt))
				rt_reset(rt);
			if (rt_rot_event(key, RS->sl_obj))
				rt_reset(rt);
		}
		if (key == K_N)
			RS->sl_obj = (RS->sl_obj) ? RS->sl_obj->next : RS->object;//=wsl!
	}
	return (0);
}
