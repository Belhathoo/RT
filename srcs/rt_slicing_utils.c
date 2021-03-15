/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_slicing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:44:19 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/15 18:44:27 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		rt_slice_ax(t_object *o)
{
	o->sl_pnt = o->pos;
	if (o->sl_ax == 1)
		o->sl_vec = o->rot;
	else if (o->sl_ax == 2)
		o->sl_vec = o->vec2;
	else if (o->sl_ax == 3)
		o->sl_vec = o->vec1;
}

int			rt_one_slice(t_object *o, t_ray *r, t_hit *rec)
{
	t_slice	s;

	s.p0 = vec_ray(r, rec->t);
	s.ax = vec_unit(o->sl_vec);
	s.my0 = vec_unit(vec_sub(rec->p, o->pos));
	if (vec_dot(s.my0, s.ax) < -0.001)
		return (0);
	return (1);
}

t_object	rt_sl_plan(t_object *o, t_vec ax)
{
	t_object plan;

	plan.pos = o->sl_pnt;
	plan.rot = vec_pro_k(ax, -1);
	plan.col = o->col;
	plan.noi = o->noi;
	plan.txt = o->txt;
	plan.mat = o->mat;
	return (plan);
}

int			in_sphere(t_object *o)
{
	if (vec_length(vec_sub(o->sl_pnt, o->pos)) >= o->radius)
		return (0);
	return (1);
}
