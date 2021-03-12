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

//place after get repere
int		rt_slice_ax(t_object *o, char *str)
{
	o->sl_pnt = o->pos;
	if (ft_strcmp(str, "z"))
		o->sl_vec = o->rot;
	else if (ft_strcmp(str, "y"))
		o->sl_vec = o->vec2;
	else if (ft_strcmp(str, "x"))
		o->sl_vec = o->vec1;
	else
		return (0);
	return (1);
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
	if (vec_length(vec_sub(o->sl_pnt, o->pos)) >= o->radius)
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
	if (c >= o->radius)
		return (0);
	return (1);
}

int			inside_slicing(t_object *o, t_ray *r, t_hit *rec)
{
	t_slice s;

	s.p0 = vec_ray(r, rec->t0);
	s.p1 = vec_ray(r, rec->t1);
	s.ax = vec_unit(o->sl_vec);
  	s.my0 = vec_unit(vec_sub(s.p0, o->sl_pnt));
	s.my1 = vec_unit(vec_sub(s.p1, o->sl_pnt));
	s.s0 = vec_dot(s.my0, s.ax);
	s.s1 = vec_dot(s.my1, s.ax);
	if (s.s0 <= 0 && s.s1 <= 0)
		return (0);
	if (s.s0 > 0 && s.s1 > 0)
		return (1);
	if ((s.s0 > 0 && s.s1 <= 0))
	{
		rt_plan_intersect(o, s, rec, r, rec->t0);
		return (1);
	}
	return (0);
}

int		rt_plan_intersect(t_object *o, t_slice s, t_hit *rec, t_ray *r, double t)
{
	ft_memcpy(&s.recp, rec, sizeof(t_hit));
	s.plan = rt_sl_plan(o, s.ax);
	rt_init_negative(&s.recp);
	s.ret = rt_hit_plan(&s.plan, r, &s.recp);
	if (rt_hit_plan(&s.plan, r, &s.recp) == 1 && s.recp.t < t)
	{
		rec->tx = 1;
		rec->t0 = s.recp.t;
		return (1);
	}
	else
		return 0;
}

int			rt_slicing(t_object *o, t_ray *r, t_hit *rec)
{
	t_slice	s;

	rec->tx = 0;
	if (rec->t1 <= EPS)
		return(inside_slicing(o, r, rec));
	s.p0 = vec_ray(r, rec->t0);
  	s.ax = vec_unit(o->sl_vec);
  	s.my0 = vec_unit(vec_sub(s.p0, o->sl_pnt));
	if (vec_dot(s.my0, s.ax) <= 0)
	{
		s.p1 = vec_ray(r, rec->t1);
		s.my1 = vec_unit(vec_sub(s.p1, o->sl_pnt));
		if (vec_dot(s.my1, s.ax) <= 0)
			return (0);
		return (rt_plan_intersect(o, s, rec, r, rec->t1));
	}
	return 1;
}