/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light_shading.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:54:57 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/01 17:31:22 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int				rt_shading(t_thread *th, t_ray sh_r, t_light *l, t_vec *col)
{
	t_hit	    rec;
	t_object	*o;
	t_vec		color;
	t_vec		l_vec;

	l_vec = sh_r.dir;
	sh_r.dir = vec_unit(sh_r.dir);
	// sh_r.origin = vec_add(pnt, vec_pro_k(sh_r.dir, 0.001));


	if (rt_hit(th->rt->scene, &sh_r, &rec, vec_length(l_vec)))
	{
		o = rec.curr_obj;
		if (o->refr == 0)
			return (1);
		else
		{
			sh_r = rt_refraction(rec, sh_r, o);
			if(rt_shading(th, sh_r, l, col))
				return (1);
			else
				*col =vec_add(*col, vec_pro_k(*col, 0.5));
				// return (1);
		}
	}
	return (0);
}

void			rt_ambient(double amb, t_light *l, t_hit rec, t_vec *col)
{
	t_object	*o;
	double		ia;
	t_vec		c;
	/*
	   recheck !!
	   */
	c = vec(0.0, 0.0, 0.0);
	o = rec.curr_obj;

	ia = amb;
	*col = vec_pro_k(rec.col, ia);
	if (l)
		*col = vec_prod(*col, o->mat.ka);
}
