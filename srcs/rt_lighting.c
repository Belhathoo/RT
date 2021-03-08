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

t_vec		rt_lighting(t_thread *th, t_light *l)
{
	double	f_att;
	t_vec	color;
	t_ray	sh_r;

	t_vec	l_vec;
	color = vec3(0.0);
	rt_ambient(th->rt->scene->ambient, l, th->rec, &color);
	while (l)
	{
		// if (l->type == PL_LIGHT) 
		// 	l_vec = vec_pro_k(l->dir, -1.0);
		// else
			l_vec = vec_sub(l->pos, th->rec.p);
		
		sh_r.dir = vec_unit(l_vec);
		sh_r.origin = vec_add(th->rec.p, vec_pro_k(sh_r.dir, 0.01));
		if (rt_shading(th, sh_r, l, &color) == 0)
		{
			f_att = /*(l->type == PL_LIGHT) ? 1.0 : */ft_clamping(1 / ((vec_length(l_vec)\
					+ vec_length(th->rec.ray->dir)) * 0.02));
			color = vec_add(color, vec_add(rt_specular(th->rec, l, l_vec, f_att),\
						rt_diffuse(th->rec, l, l_vec, f_att)));
		}
		l = l->next;
	}
	return (color);
}
