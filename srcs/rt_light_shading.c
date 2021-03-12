/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light_shading.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:27:31 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/12 19:27:32 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

/*
   if pl light no att, intensity = 1.0 fix ?
   */
int			rt_shading(t_thread *th, t_ray sh_r, t_light *l, t_vec *col\
				, int depth)
{
	t_hit		rec;
	t_object	*o;
	int			shade;
	double		closest;
	t_ray		sc_r;
	t_vec		l_vec;
	double		dot;

	shade = 0;
	l_vec = (l->type == PL_LIGHT) ?\
			vec_pro_k(l->dir, -1.0) : vec_sub(l->pos, th->rec.p);
	closest = (l->type == PL_LIGHT) ? 10000.0 : vec_length(l_vec);
	rec.curr_obj = NULL;
	if (rt_hit(th->rt->scene, &sh_r, &rec, closest) && (shade = 1))
		o = rec.curr_obj;
	if (depth > 1 && shade && o->refr != 0.0)
	{
		// if (!o->txt.is_txt || o->txt.is_trans) recheck ( problem for refr < 1 previously !!)
		{
			sc_r = rt_refraction(rec, sh_r, o);
			/* refract dont stock sc dir for reflected! {segfault} 
			// create separated fresnel function (aka change some of rt_refract && rt_refraction)
			*/
			dot = vec_dot(vec_unit(sc_r.dir), vec_unit(l_vec));
			if ((dot > 0.40))
			{
				*col = vec_pro_k(*col, dot * o->refr * 0.7);
				return (rt_shading(th, sc_r, l, col, depth - 1));
			}
		}
	}
	return (shade);
}

void			rt_ambient(double amb, t_light *l, t_hit rec, t_vec *col)
{
	t_object	*o;

	o = rec.curr_obj;
	*col = vec_add(*col, vec_pro_k(rec.col, amb));
	if (l)
		*col = vec_add(*col, vec_prod(*col, o->mat.ka));
}
