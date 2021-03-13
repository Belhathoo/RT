/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_lighting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:55:26 by belhatho          #+#    #+#             */
/*   Updated: 2021/02/18 15:55:29 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vec		rt_diffuse(t_hit rec, t_light *l, t_vec lo, double f_att)
{
	double	d;
	t_vec	diff;

	d = ffmax(0.0, vec_dot(vec_unit(lo), rec.n)) * l->intensity;
	diff = vec_prod(rec.col, l->col);
	diff = vec_prod(diff, vec_pro_k(rec.curr_obj->mat.kd, d * f_att));
	return (diff);
}

t_vec		rt_specular(t_hit rec, t_light *l, t_vec lo, double f_att)
{
	t_object	*o;
	double		s;
	t_vec		spec;
	t_vec		refl;

	o = rec.curr_obj;
	refl = vec_unit((rt_reflect(vec_unit(lo), rec.n)));
	s = pow(ffmax(0.0, vec_dot(refl,
					vec_unit(rec.ray->dir))), o->mat.shininess);
	s *= l->intensity;
	spec = vec_add(rec.col, l->col);
	spec = vec_prod(spec, vec_pro_k(o->mat.ks, s * f_att));
	return (spec);
}


t_sh_ray	rt_init_sh_ray(t_vec p, t_light *l)
{
	t_sh_ray	sh_r;

	sh_r.l_vec = (l->type == PL_LIGHT) ?\
		     vec_pro_k(l->dir, -1.0) : vec_sub(l->pos, p);
	sh_r.r.dir = vec_unit(sh_r.l_vec);
	sh_r.r.origin = vec_add(p, vec_pro_k(sh_r.r.dir, 0.001));
	sh_r.l = l;
	return (sh_r);
}

t_vec		rt_lighting(t_thread *th, t_light *l)
{
	double	f_att;
	t_vec	col;
	t_sh_ray	sh_r;

	rt_ambient(th->rt->scene->ambient, l, th->rec, &col);
	while (l)
	{
		sh_r = rt_init_sh_ray(th->rec.p, l);
		if (rt_shading(th, sh_r, &col, MAX_DEPTH) == 0)
		{
			f_att = (l->type == PL_LIGHT) ? 1.0\
				: ft_clamping(1 / ((vec_length(sh_r.l_vec)\
								+ vec_length(th->rec.ray->dir)) * 0.02));
			col = vec_add(col, vec_add(rt_specular(th->rec, l, sh_r.l_vec, f_att),\
						rt_diffuse(th->rec, l, sh_r.l_vec, f_att)));
		}
		l = l->next;
	}
	return (col);
}

// double		angle_between(t_vec a, t_vec b)
// {
// 	return (acos(vec_dot(a, b) / (vec_length(a) * vec_length(b))));
// }
// typedef struct s_light_shading
// {
// 	t_vec		l_vec;
// 	t_hit		rec;
// 	double		closest;
// 	int			shade;


// }				t_li_sh;


// t_li_sh		rt_init_shade(t_sh_ray sh, t_vec p)
// {
// 	t_li_sh s;

		
// 	s.rec.curr_obj = NULL;
// 	s.l_vec = (sh.l->type == PL_LIGHT) ?\
// 		 vec_pro_k(sh.l->dir, -1.0) : vec_sub(sh.l->pos, p);
// 	s.closest = (sh.l->type == PL_LIGHT) ? 10000.0 : vec_length(s.l_vec);
// }
