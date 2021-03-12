/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_check1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:20:35 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/11 12:06:56 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		rt_check_o_annex(t_object *o, t_rt *rt)
{
	if (o->is_sliced == 1)
	{
		if (o->sl_ax != 0)
			rt_exit(rt, o->name, ": Only one slicing is possible"\
			, EXIT_FAILURE);
		if (!ft_strcmp(o->name, "sphere") && !in_sphere(o))
			rt_exit(rt, o->name, "slicing pnt is outside the sphere!"\
			, EXIT_FAILURE);
		if (!ft_strcmp(o->name, "cylinder") && !in_cylindr(o))  // jessie
			rt_exit(rt, " ", "slicing pnt is outside the cylinder!"\
			, EXIT_FAILURE);
	}
	if (!ft_strcmp(o->name, "l_cone") && o->height >= o->width)
		rt_exit(rt, o->name, ": height should be < width. (init: w:5 h:2.5) "\
		, EXIT_FAILURE);
	if ((!ft_strcmp(o->name, "l_cylinder") || !ft_strcmp(o->name, "mobius"))\
		&& o->height <= 0.0)
		rt_exit(rt, o->name, ": height should be strictly positive. "\
		, EXIT_FAILURE);
	if (!ft_strcmp(o->name, "rectangle")\
		&& (o->height <= 0.0 || o->width <= 0.0))
		rt_exit(rt, o->name, ": height & width should be strictly positive. "\
		, EXIT_FAILURE);
}

void		rt_all_clamp(t_object *o)
{
	rt_adjustment(&o->col);
	if (o->noi.is_noise)
	{
		rt_adjustment(&o->noi.col1);
		rt_adjustment(&o->noi.col2);
	}
	rt_set_coef(o);
	if (o->refr == 0.0)
		o->refr = o->mat.kt;
	if (o->refl == 0.0)
		o->refl = o->mat.kr;
}

void		rt_check_obj(t_object *o, t_rt *rt)
{
	if (o->name == NULL)
		rt_exit(rt, "Object", " shoud have a name!", EXIT_FAILURE);
	if (o->dir.x == 0 && o->dir.y == 0 && o->dir.z == 0)
		rt_exit(rt, o->name, ": direction vector is non-zero!", EXIT_FAILURE);
	if (o->size <= 0.0 || o->radius <= 0.0 || o->r <= 0)
		rt_exit(rt, o->name, ": radius/r/size should be positive"\
		, EXIT_FAILURE);
	if (o->angle <= 0.0 || o->angle > 180.0)
		rt_exit(rt, o->name, ": angle should be in ]0-180[", EXIT_FAILURE);
	if (o->txt.is_txt == 1 && o->noi.is_noise == 1)
		rt_exit(rt, o->name, ": either texture either noise", EXIT_FAILURE);
	if (o->refr != 0.0 && (o->refr < 01.00 || o->refr > 10.0))
		rt_exit(rt, o->name, ": refraction coef should be >= 1.0."\
		, EXIT_FAILURE);
	if (o->scale <= 0.0)
		rt_exit(rt, o->name, "scale should be strictly positive", EXIT_FAILURE);
	rt_check_o_annex(o, rt);
	o->angle = degtorad(o->angle) / 2;
	o->rot = rotation(o->dir, o->rot);
	rt_get_repere(o);
	(o->sl_ax != 0) ? rt_slice_ax(o) : 0;
	rt_comp_obj(o, rt); //// events...
	rt_all_clamp(o);
}
