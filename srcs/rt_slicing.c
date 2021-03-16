/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_slicing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 19:19:52 by msoulaim          #+#    #+#             */
/*   Updated: 2021/03/15 18:12:50 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

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
		s.t = rec->t0;
		rt_plan_intersect(o, s, rec, r);
		return (1);
	}
	return (0);
}

int			rt_plan_intersect(t_object *o, t_slice s, t_hit *rec, t_ray *r)
{
	ft_memcpy(&s.recp, rec, sizeof(t_hit));
	s.plan = rt_sl_plan(o, s.ax);
	rt_init_negative(&s.recp);
	s.ret = rt_hit_plan(&s.plan, r, &s.recp);
	if ((rt_hit_plan(&s.plan, r, &s.recp) == 1) && (s.recp.t < s.t))
	{
		rec->tx = 1;
		rec->t0 = s.recp.t;
		return (1);
	}
	else
		return (0);
}

int			rt_slicing(t_object *o, t_ray *r, t_hit *rec)
{
	t_slice	s;

	rec->tx = 0;
	if (rec->t1 <= EPS)
		return (inside_slicing(o, r, rec));
	s.p0 = vec_ray(r, rec->t0);
	s.ax = vec_unit(o->sl_vec);
	s.my0 = vec_unit(vec_sub(s.p0, o->sl_pnt));
	if (vec_dot(s.my0, s.ax) <= 0)
	{
		s.p1 = vec_ray(r, rec->t1);
		s.my1 = vec_unit(vec_sub(s.p1, o->sl_pnt));
		s.t = rec->t1;
		if (vec_dot(s.my1, s.ax) <= 0)
			return (0);
		return (rt_plan_intersect(o, s, rec, r));
	}
	return (1);
}
