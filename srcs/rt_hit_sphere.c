/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hit_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:31:37 by ibel-kha          #+#    #+#             */
/*   Updated: 2021/03/15 17:00:39 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vec	ft_rot_vec(t_vec a, t_vec b, double t)
{
	t_vec	res;

	res.x = (b.x * b.x + (1.0 - b.x * b.x) * cos(t)) * a.x + (b.x * b.y
			* (1.0 - cos(t)) - b.z * sin(t)) * a.y + (b.x * b.z
			* (1.0 - cos(t)) + b.y * sin(t)) * a.z;
	res.y = (b.x * b.y * (1.0 - cos(t)) + b.z * sin(t)) * a.x
		+ (b.y * b.y + (1.0 - b.y * b.y) * cos(t)) * a.y
		+ (b.y * b.z * (1.0 - cos(t)) - b.x * sin(t)) * a.z;
	res.z = (b.x * b.z * (1.0 - cos(t)) - b.y * sin(t)) * a.x
		+ (b.y * b.z * (1.0 - cos(t)) + b.x * sin(t)) * a.y
		+ (b.z * b.z + (1.0 - b.z * b.z) * cos(t)) * a.z;
	return (res);
}

void	sphere_uv(t_object *o, t_hit *rec)
{
	double	phi;
	double	theta;
	t_vec	p;

	p = vec_sub(rec->p, o->pos);
	p = ft_rot_vec(p, o->rot, o->txt.mv1);
	p = ft_rot_vec(p, o->vec1, o->txt.mv2);
	p = vec(vec_dot(p, o->vec1), vec_dot(p, o->rot), vec_dot(p, o->vec2));
	phi = atan2(p.z, p.x);
	theta = asin(p.y / o->radius);
	rec->u = (phi + M_PI) / (2.0 * M_PI);
	rec->v = (theta + M_PI / 2.0) / M_PI;
	rec->u = rt_frac(rec->u);
	rec->v = rt_frac(rec->v);
	return ;
}

int		rt_sphere_params(t_object *obj, t_ray *ray, t_hit *rec)
{
	rec->or = vec_sub(ray->origin, obj->pos);
	rec->a = vec_dot(ray->dir, ray->dir);
	rec->b = 2.0 * vec_dot(rec->or, ray->dir);
	rec->c = vec_dot(rec->or, rec->or) - (obj->radius * obj->radius);
	rec->delta = rec->b * rec->b - 4.0 * rec->a * rec->c;
	if (rec->delta >= 0.0)
	{
		rec->t0 = (-rec->b - sqrt(rec->delta)) / (2 * rec->a);
		rec->t1 = (-rec->b + sqrt(rec->delta)) / (2 * rec->a);
		(rec->t0 < rec->t1) ? 0 : ft_float_swap(&rec->t0, &rec->t1);
		(rec->t0 <= EPS) ? ft_float_swap(&rec->t0, &rec->t1) : 0;
		return (1);
	}
	return (0);
}

int		rt_hit_sphere(t_object *o, t_ray *ray, t_hit *rec)
{
	if (rt_sphere_params(o, ray, rec))
	{
		if ((o->is_sl == 1 || o->sl_ax) && rt_slicing(o, ray, rec) == 0)
			return (0);
		if (negative(rec) == 0)
			return (0);
		if (rec->t > EPS && rec->t < rec->closest)
		{
			rec->p = vec_ray(ray, rec->t);
			if (rec->tx == 1)
				rec->n = vec_pro_k(o->sl_vec, -1);
			else if (rec->is_n == 1 && rec->t == rec->neg[1])
				rec->n = rec->neg_n;
			else if (rec->t1 <= EPS)
				rec->n = vec_div_k(vec_sub(rec->p, o->pos), -o->radius);
			else
				rec->n = vec_div_k(vec_sub(rec->p, o->pos), o->radius);
			sphere_uv(o, rec);
			if (o->txt.is_txt && o->txt.is_trans && \
					!(trans_texture(ray, o, rec)))
				return (0);
			return (1);
		}
	}
	return (0);
}
