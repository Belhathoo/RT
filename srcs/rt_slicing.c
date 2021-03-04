/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_slicing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 19:19:52 by msoulaim          #+#    #+#             */
/*   Updated: 2021/03/04 15:44:28 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_object rt_sl_plan(t_object *o, t_vec ax)
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

int		in_sphere(t_object *o)
{
	if (vec_length(vec_sub(o->sl_pnt, o->pos)) >= o->size)
		return (0);
	return (1);
}

int		in_cylindr(t_object *o)
{
	//// recheck !!
	t_vec a;
	t_vec b;
	double c;

	a = vec_sub(o->pos, o->sl_pnt);
	b = vec_cross(a, o->rot);
	c = vec_length(b) / vec_length(o->rot);
	if (c >= o->size)
		return (0);
	return (1);
}

int			rt_slicing(t_object *o, t_ray *r, t_hit *rec)
{
	t_vec     ax;
	t_vec     my;
  	t_object  plan;
	t_vec	p;
	t_hit	recp;
	int		ret;

	rec->tx = 0;
	p = vec_ray(r, rec->t0);
  	ax = vec_unit(o->sl_vec);
  	my = vec_unit(vec_sub(p, o->sl_pnt));
	if (vec_dot(my, ax) <= 0)
	{
		p = vec_ray(r, rec->t1);
		my = vec_unit(vec_sub(p, o->sl_pnt));
		if (vec_dot(my, ax) <= 0)
			return (0);
		ft_memcpy(&recp, rec, sizeof(t_hit));
		plan = rt_sl_plan(o, ax);
		rt_init_negative(&recp);
		ret = rt_hit_plan(&plan, r, &recp);
		if (ret == 1 && recp.t < rec->t1)
		{
			rec->tx = 1;
			rec->t0 = recp.t;
			o->sl_sl = recp.t;
			return (1);
		}
		else
			return 0;
	}
	return 1;
}