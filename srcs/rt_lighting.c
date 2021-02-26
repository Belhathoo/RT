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

t_vec		rt_lighting(t_thread *th, t_hit rec, t_light *l)
{
	t_vec		l_vec;
	double f_att = 0;
	t_vec	color;

	color = vec3(0.0);
	rt_ambient(th->rt->scene->ambient, l, rec, &color);
	while (l)
	{
		l_vec = vec_sub(l->pos, rec.p);
		if (rt_shading(th, rec, l, l_vec, &color) == 0)
		{
			f_att = ft_clamping(1 / ((vec_length(l_vec)\
					+ vec_length(rec.ray->dir)) * 0.02));
			color = vec_add(color, vec_add(rt_specular(rec, l, l_vec, f_att),\
						rt_diffuse(rec, l, l_vec, f_att)));
		}
		l = l->next;
	}
	th->rec.col =  color;
	return (color);
}
