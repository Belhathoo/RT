/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_events_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 11:29:47 by belhatho          #+#    #+#             */
/*   Updated: 2021/02/27 11:29:59 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <rt.h>

int    rt_move(int key, t_vec *vec)
{
	if (key == K_T)
		vec->z += 1;
	else if (key == K_R)
		vec->z -= 1;
	else if (key == K_UP)
		vec->y += 1;
	else if (key == K_DWN)
		vec->y -= 1;
	else if (key == K_LFT )
		vec->x -= 1;
	else if (key == K_RGHT)
		vec->x += 1;   
	else
		return (0);
	// ft_putendl("rt_move--here!");
	return(1);
}
t_vec		rt_rot_pnt(t_object *o, t_vec (*rot_ax)(t_vec vec, double angle), double angle)
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

int     rt_rot_event(int key, t_object *o)
{
	if (key == K_X)
	{
		o->rot = rt_rotX(o->rot, 2.5);
		o->vec2 = rt_rotX(o->vec2, 2.5);
		o->vec1 = rt_rotX(o->vec1, 2.5);
		o->sl_vec = rt_rotX(o->sl_vec, 2.5);
		o->sl_pnt = rt_rot_pnt(o, rt_rotX, 2.5);
	}
    else if (key == K_W)
	{
		o->rot = rt_rotX(o->rot, -2.5);
		o->vec2 = rt_rotX(o->vec2, -2.5);
		o->vec1 = rt_rotX(o->vec1, -2.5);
		o->sl_vec = rt_rotX(o->sl_vec, -2.5);
		o->sl_pnt = rt_rot_pnt(o, rt_rotX, -2.5);
	}
	else if (key == K_Y)
	{
		o->rot = rt_rotY(o->rot, 2.5);
		o->vec2 = rt_rotY(o->vec2, 2.5);
		o->vec1 = rt_rotY(o->vec1, 2.5);
		o->sl_vec = rt_rotY(o->sl_vec, 2.5);
		o->sl_pnt = rt_rot_pnt(o, rt_rotY, 2.5);
	}
    else if (key == K_T)
	{
		o->rot = rt_rotY(o->rot, -2.5);
		o->vec2 = rt_rotY(o->vec2, -2.5);
		o->vec1 = rt_rotY(o->vec1, -2.5);
		o->sl_vec = rt_rotY(o->sl_vec, -2.5);
		o->sl_pnt = rt_rot_pnt(o, rt_rotY, -2.5);
	}
	else if (key == K_Z)
	{
		o->rot = rt_rotZ(o->rot, 2.5);
		o->vec2 = rt_rotZ(o->vec2, 2.5);
		o->vec1 = rt_rotZ(o->vec1, 2.5);
		o->sl_vec = rt_rotZ(o->sl_vec, 2.5);
		o->sl_pnt = rt_rot_pnt(o, rt_rotZ, 2.5);
    }
    else if (key == K_E)
	{
		o->rot = rt_rotZ(o->rot, -2.5);
		o->vec2 = rt_rotZ(o->vec2, -2.5);
		o->vec1 = rt_rotZ(o->vec1, -2.5);
		o->sl_vec = rt_rotZ(o->sl_vec, -2.5);
		o->sl_pnt = rt_rot_pnt(o, rt_rotZ, -2.5);
    }
    else
        return(0);
   	// ft_putendl("rt_rot--here!");
    return (1);
}

