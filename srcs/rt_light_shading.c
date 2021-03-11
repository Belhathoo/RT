/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light_shading.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:54:57 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/08 15:53:51 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int				rt_shading(t_thread *th, t_ray sh_r, t_light *l, t_vec *col\
			, int depth)
{
	t_hit	    rec;
	t_object	*o;
	int			shade;
	double		closest;
	t_ray		sc_r;
	t_vec		l_vec;

	shade =  0;
	l_vec = vec_sub(l->pos, th->rec.p);
	// sh_r.dir = vec_unit(sh_r.dir);
	closest = /* (l->type == PL_LIGHT) ? 8000.0 : */vec_length(l_vec);
	rec.curr_obj = NULL;
	if (rt_hit(th->rt->scene, &sh_r, &rec, closest) && (shade = 1))
		o = rec.curr_obj;
	if (depth > 1 && shade && o->refr != 0.0)
	{
		// if (!o->txt.is_txt || o->txt.is_trans)
		{
			sc_r = rt_refraction(rec, sh_r, o);
			double dot = vec_dot(vec_unit(sc_r.dir), vec_unit(l_vec));
			if ((dot > 0.40))
			{
				*col = vec_pro_k(*col, dot * o->refr * 0.9);
				return(rt_shading(th, sc_r, l, col, depth - 1));
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
