/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_events_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 11:29:47 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/13 16:05:03 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int		rt_move(int key, t_vec *vec)
{
	if (key == K_NP_PLU)
		vec->z += 0.987654321;
	else if (key == K_NP_MIN)
		vec->z -= 0.987654321;
	else if (key == K_UP)
		vec->y += 0.987654321;
	else if (key == K_DWN)
		vec->y -= 0.987654321;
	else if (key == K_LFT)
		vec->x -= 0.987654321;
	else if (key == K_RGHT)
		vec->x += 0.987654321;
	else
		return (0);
	return (1);
}

int		rt_event_ann(int key, t_object *o)
{
	if (key == K_Y)
	{
		o->rot = rt_roty(o->rot, 1.72);
		o->vec2 = rt_roty(o->vec2, 1.72);
		o->vec1 = rt_roty(o->vec1, 1.72);
		o->sl_vec = rt_roty(o->sl_vec, 1.72);
		o->sl_pnt = rt_rot_pnt(o, rt_roty, 1.72);
	}
	else if (key == K_V)
	{
		o->rot = rt_roty(o->rot, -1.72);
		o->vec2 = rt_roty(o->vec2, -1.72);
		o->vec1 = rt_roty(o->vec1, -1.72);
		o->sl_vec = rt_roty(o->sl_vec, -1.72);
		o->sl_pnt = rt_rot_pnt(o, rt_roty, -1.72);
	}
	else
		return (0);
	return (1);
}

int		rt_event_ann1(int key, t_object *o)
{
	if (key == K_X)
	{
		o->rot = rt_rotx(o->rot, 1.72);
		o->vec2 = rt_rotx(o->vec2, 1.72);
		o->vec1 = rt_rotx(o->vec1, 1.72);
		o->sl_vec = rt_rotx(o->sl_vec, 1.72);
		o->sl_pnt = rt_rot_pnt(o, rt_rotx, 1.72);
	}
	else if (key == K_U)
	{
		o->rot = rt_rotx(o->rot, -1.72);
		o->vec2 = rt_rotx(o->vec2, -1.72);
		o->vec1 = rt_rotx(o->vec1, -1.72);
		o->sl_vec = rt_rotx(o->sl_vec, -1.72);
		o->sl_pnt = rt_rot_pnt(o, rt_rotx, -1.72);
	}
	else
		return (0);
	return (1);
}

int		rt_rot_event(int key, t_object *o)
{
	if (rt_event_ann(key, o))
		return (1);
	else if (rt_event_ann1(key, o))
		return (1);
	else if (key == K_Z)
	{
		o->rot = rt_rotz(o->rot, 1.72);
		o->vec2 = rt_rotz(o->vec2, 1.72);
		o->vec1 = rt_rotz(o->vec1, 1.72);
		o->sl_vec = rt_rotz(o->sl_vec, 1.72);
		o->sl_pnt = rt_rot_pnt(o, rt_rotz, 1.72);
	}
	else if (key == K_W)
	{
		o->rot = rt_rotz(o->rot, -1.72);
		o->vec2 = rt_rotz(o->vec2, -1.72);
		o->vec1 = rt_rotz(o->vec1, -1.72);
		o->sl_vec = rt_rotz(o->sl_vec, -1.72);
		o->sl_pnt = rt_rot_pnt(o, rt_rotz, -1.72);
	}
	else
		return (0);
	return (1);
}
