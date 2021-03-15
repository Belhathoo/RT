/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hit_torus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:42:47 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/15 17:42:52 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void			torus_uv(t_hit *rec, t_object *o)
{
	t_vec	p;
	double	phi;
	double	theta;
	double	tmp;

	p = vec_pro_k(vec_sub(rec->p, o->pos), 1.0);
	p = vec(vec_dot(p, o->vec1), vec_dot(p, o->rot), vec_dot(p, o->vec2));
	phi = atan2(p.z, p.x);
	tmp = p.x * p.x + p.z * p.z;
	theta = atan2(p.y, (sqrt(tmp))) - o->radius;
	rec->u = 0.5 + phi / 2 * M_PI;
	rec->v = 0.5 + theta / 2 * M_PI;
	rec->u = rec->u - floor(rec->u);
	rec->v = rec->v - floor(rec->v);
}

t_vec			rt_torus_normal(t_ray *ray, t_hit *rec, t_object *obj)
{
	t_vec	normal;
	double	k;
	double	m;
	t_vec	a;
	t_vec	v;

	a = ray->dir;
	v = vec_unit(obj->rot);
	k = vec_dot(vec_sub(rec->p, obj->pos), v);
	a = vec_sub(rec->p, vec_pro_k(v, k));
	m = obj->r * obj->r - k * k;
	m = sqrt(m);
	normal = vec_sub(rec->p, vec_sub(a, vec_pro_k(vec_sub(obj->pos, a),
					m / obj->radius + m)));
	normal = vec_unit(normal);
	return (normal);
}

static int		rt_torus_params(t_ray *ray, t_hit *record, t_object *obj)
{
	t_coef c;
	double coe[5];

	record->or = vec_sub(ray->origin, obj->pos);
	c.m = vec_dot(ray->dir, ray->dir);
	c.n = vec_dot(ray->dir, record->or);
	c.o = vec_dot(record->or, record->or);
	c.p = vec_dot(ray->dir, obj->rot);
	c.q = vec_dot(record->or, obj->rot);
	coe[0] = c.o * c.o - 2 * c.o * (obj->radius * obj->radius\
		+ obj->r * obj->r) + 4 * obj->radius * obj->radius * c.q * c.q\
		+ pow((obj->radius * obj->radius - obj->r * obj->r), 2);
	coe[1] = 4 * c.n * c.o - 4 * c.n *\
		(obj->radius * obj->radius + obj->r * obj->r)\
		+ 8 * obj->radius * obj->radius * c.p * c.q;
	coe[2] = 4 * c.n * c.n + 2 * c.m * c.o - 2 * c.m\
			* (obj->radius * obj->radius + obj->r * obj->r)\
			+ 4 * obj->radius * obj->radius * c.p * c.p;
	coe[3] = 4 * c.m * c.n;
	coe[4] = c.m * c.m;
	return (rt_check_distance(coe, record));
}

int				rt_hit_torus(t_object *obj, t_ray *ray, t_hit *record)
{
	if (rt_torus_params(ray, record, obj))
	{
		record->p = vec_ray(ray, record->t);
		record->n = rt_torus_normal(ray, record, obj);
		torus_uv(record, obj);
		return (1);
	}
	return (0);
}
