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

double		angle_between(t_vec a, t_vec b)
{
	return (acos(vec_dot(a, b) / (vec_length(a) * vec_length(b))));
}

void		rt_ambient(double amb, t_light *l, t_hit rec, t_vec *col)
{
	t_object	*o;

	o = rec.curr_obj;
	*col = vec_add(vec3(0.0), vec_pro_k(rec.col, amb));
	if (l)
		*col = vec_add(*col, vec_prod(*col, o->mat.ka));
}

t_li_sh		rt_init_shade(t_sh_ray sh, t_vec p)
{
	t_li_sh s;

	s.o = NULL;
	s.rec.curr_obj = NULL;
	s.l_vec = (sh.l->type == PL_LIGHT) ?\
		vec_pro_k(sh.l->dir, -1.0) : vec_sub(sh.l->pos, p);
	s.closest = (sh.l->type == PL_LIGHT) ? 10000.0 : vec_length(s.l_vec);
	return (s);
}

int			rt_shading(t_thread *th, t_sh_ray sh_r, t_vec *col, int depth)
{
	int			shade;
	t_sh_ray	sc_r;
	double		dot;
	t_li_sh		s;

	s = rt_init_shade(sh_r, th->rec.p);
	shade = 0;
	if (rt_hit(th->rt->scene, &sh_r.r, &(s.rec), s.closest) && (shade = 1))
		s.o = s.rec.curr_obj;
	if (depth > 1 && shade && s.o->refr != 0.0)
	{
		sc_r.r = rt_refraction(s.rec, sh_r.r, s.o);
		sc_r.l = sh_r.l;
		dot = vec_dot(vec_unit(sc_r.r.dir), vec_unit(s.l_vec));
		if ((dot > 0.40))
		{
			*col = vec_pro_k(*col, dot * s.o->refr * 0.8);
			return (rt_shading(th, sc_r, col, depth - 1));
		}
	}
	return (shade);
}
