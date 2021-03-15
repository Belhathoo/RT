/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rotation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:11:10 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/11 19:11:18 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vec		rt_rotz(t_vec vec, double angle)
{
	t_vec	newv;

	newv.x = cos(degtorad(angle)) * vec.x - sin(degtorad(angle)) * vec.y;
	newv.y = cos(degtorad(angle)) * vec.y + sin(degtorad(angle)) * vec.x;
	newv.z = vec.z;
	return (newv);
}

t_vec		rt_rotx(t_vec vec, double angle)
{
	t_vec	newv;

	newv.y = cos(degtorad(angle)) * vec.y - sin(degtorad(angle)) * vec.z;
	newv.z = cos(degtorad(angle)) * vec.z + sin(degtorad(angle)) * vec.y;
	newv.x = vec.x;
	return (newv);
}

t_vec		rt_roty(t_vec vec, double angle)
{
	t_vec	newv;

	newv.z = cos(degtorad(angle)) * vec.z - sin(degtorad(angle)) * vec.x;
	newv.x = cos(degtorad(angle)) * vec.x + sin(degtorad(angle)) * vec.z;
	newv.y = vec.y;
	return (newv);
}

t_vec		rotation(t_vec dir, t_vec rot)
{
	return (rt_roty(rt_rotz(rt_rotx(dir, rot.x), rot.z), rot.y));
}

t_vec		rt_rot_pnt(t_object *o, t_vec (*rot_ax)(t_vec vec, double angle)
			, double angle)
{
	t_vec	tmp;
	t_vec	rot;
	double	dist;

	tmp = vec_sub(o->sl_pnt, o->pos);
	dist = vec_length(tmp);
	rot = vec_unit(tmp);
	rot = rot_ax(rot, angle);
	tmp = vec_add(o->pos, vec_pro_k(rot, dist));
	return (tmp);
}
