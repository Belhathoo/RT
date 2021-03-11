/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ref.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 10:54:47 by belhatho          #+#    #+#             */
/*   Updated: 2021/02/22 10:55:14 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <rt.h>


t_vec		rt_reflect(t_vec v, t_vec n)
{
	return (vec_sub(v, vec_pro_k(vec_pro_k(n, 2), vec_dot(v, n))));
}

int       rt_refract(t_vec i, t_vec n, float ior, t_vec *rf)
{
	int		ret;
	t_vec	ui;
	float	dot;
	float	delta;

	ret = 0;
	ui = vec_unit(i);
	dot = vec_dot(ui, n);
	delta = 1.0 - ior * ior * (1 - dot * dot);
	if (delta > 0)
	{
		*rf = vec_unit(vec_sub(vec_pro_k(vec_sub(ui, vec_pro_k(n, dot)), ior),\
				vec_pro_k(n, sqrt(delta))));
		ret = 1; 
	}
	return (ret);
}

t_ray		rt_reflection(t_hit rec, t_ray r)
{
	t_ray	rf;

	rf.dir = rt_reflect(r.dir, rec.n);
	rf.origin = vec_add(rec.p, vec_pro_k(rf.dir, 0.001));
	return (rf);
}

t_ray		rt_refraction(t_hit rec, t_ray r, t_object *o)
{
	t_ray	rt;
	t_vec	out_n;
	t_vec 	refl;
	float	ior;


		refl = rt_reflect(r.dir, rec.n);
		if (vec_dot(r.dir, rec.n) > 0.0)
		{
			out_n = vec_pro_k(rec.n, -1.0);
			ior = o->refr;
		}
		else
		{
			out_n = rec.n;
			ior = 1 / o->refr;
		}
		if (rt_refract(r.dir, out_n, ior, &rt.dir) == 0)
			rt.dir = refl;
		rt.origin = vec_add(rec.p, vec_pro_k(rt.dir, 0.001));
		return (rt);
}
