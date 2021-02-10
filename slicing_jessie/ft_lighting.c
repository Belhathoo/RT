/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lighting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 01:52:44 by belhatho          #+#    #+#             */
/*   Updated: 2020/12/09 04:00:08 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec		ft_reflect(t_vec v, t_vec n)
{
	return (ft_minus(v, ft_pro_k(ft_pro_k(n, 2), ft_dot(v, n))));
}

t_vec		ft_diffuse(t_thread *th, t_light *l, t_vec lo, double f_att)
{
	double	d;
	t_vec	diff;

	d = th->rec.curr_obj->kd * l->intensity;
	d *= ffmax(0.0, ft_dot(ft_unit_vec(lo), th->rec.normal));
	diff = ft_produit(th->rec.curr_obj->color, l->color);
	diff = ft_pro_k(diff, d * f_att);
	return (diff);
}

t_vec		ft_specular(t_thread *th, t_light *l, t_vec lo, double f_att)
{
	t_object	*o;
	double		s;
	t_vec		spec;
	t_vec		refl;

	o = th->rec.curr_obj;
	refl = ft_unit_vec((ft_reflect(ft_unit_vec(lo), th->rec.normal)));
	s = pow(ffmax(0.0, ft_dot(refl,
						ft_unit_vec(th->rec.ray->dir))), o->shininess);
	s *= o->ks * l->intensity;
	spec = ft_plus(o->color, l->color);
	spec = ft_pro_k(spec, s * f_att);
	return (spec);
}

void		ft_phong(t_thread *th, t_light *l, t_vec lo, t_vec *d_s)
{
	double f_att;

	f_att = ft_clamping(1 /
			((ft_length(lo) + ft_length(th->rec.ray->dir)) * 0.02));
	d_s[0] = ft_plus(d_s[0], ft_diffuse(th, l, lo, f_att));
	d_s[1] = ft_plus(d_s[1], ft_specular(th, l, lo, f_att));
}

void		ft_lighting(t_thread *th, t_light *l, t_vec *c)
{
	t_object	*o;
	t_vec		l_vec;
	t_vec		d_s[2];
	int			shade;

	ft_ambient(l, th, c);
	d_s[0] = ft_vec(0.0, 0.0, 0.0);
	d_s[1] = ft_vec(0.0, 0.0, 0.0);
	o = th->rec.curr_obj;
	while (l != NULL)
	{
		l_vec = ft_minus(l->pos, th->rec.p);
		shade = ft_shading(th, l_vec);
		if (shade == 0)
			ft_phong(th, l, l_vec, d_s);
		l = l->next;
	}
	*c = ft_plus(*c, ft_plus(d_s[0], d_s[1]));
}
