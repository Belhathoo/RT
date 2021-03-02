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
	int			shade;
	double		l_vec;
	t_ray		sc_r;

	shade =  0;
	rec.curr_obj = NULL;
	l_vec = vec_length(vec_sub(l->pos, th->rec.p));
	sh_r.dir = vec_unit(sh_r.dir);
	// sh_r.origin = vec_add(pnt, vec_pro_k(sh_r.dir, 0.001));

/*
 Max && length lvec !!!!! tribich vs dell refre
*/
	if (rt_hit(th->rt->scene, &sh_r, &rec, l_vec) && (shade = 1))
		o = rec.curr_obj;
	if (shade && o->refr != 0.0)
	{
		sc_r = rt_refraction(rec, sh_r, o);
		double dot = vec_dot(sc_r.dir, sh_r.dir);
		if ((dot > 0.0))
		{
			*col = vec_pro_k(*col, dot * o->refr);
			return(rt_shading(th, sc_r, l, col));
			// return (1);
		}
		// else
	}
	return (shade);
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
