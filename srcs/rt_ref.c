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

t_vec		rt_reflection(t_thread *th, t_ray *r, t_object *o, int depth)
{
	t_ray	rf;
	t_hit	rec;

	if (depth > 1  && (o->refl > 0))
	{
		rf.dir = rt_reflect(r->dir, th->rec.n);
		rf.origin = vec_add(th->rec.p, vec_pro_k(rf.dir, 0.001));
		return (vec_pro_k(rt_raytracer(th, rec, &rf, depth -1), o->refl));
	}
	return (vec3(0.0));
}

t_vec		rt_refraction(t_thread *th, t_ray *r, t_object *o, int depth)
{
	/*o  unused replace with rt,, as refracted ray !!*/
	t_ray	rt;
	t_vec	out_n;
	t_vec 	refl;
	float	ior;
	t_hit	rec;

	if (depth > 1  && (o->refr > 0.0))
	{

		refl = rt_reflect(r->dir, th->rec.n);
		if (vec_dot(r->dir, th->rec.n) > 0.0)
		{
			out_n = vec_pro_k(th->rec.n, -1.0);
			ior = o->refr;
		}
		else
		{
			out_n = th->rec.n;
			ior = 1 / o->refr;
		}
		if (rt_refract(r->dir, out_n, ior, &rt.dir) == 0)
			rt.dir = refl;
		rt.origin = vec_add(th->rec.p, vec_pro_k(rt.dir, 0.001));
		return (rt_raytracer(th, rec, &rt, depth - 1));
	}
	return (vec3(0.0));
}
