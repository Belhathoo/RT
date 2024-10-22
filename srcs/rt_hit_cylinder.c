/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hit_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:38:30 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/16 16:22:01 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		cylinder_uv1(t_object *o, t_hit *rec)
{
	t_vec	d;

	d = vec_sub(rec->p, o->pos);
	d = vec_div_k(d, o->scale);
	d = vec(vec_dot(d, o->vec2), vec_dot(d, o->rot), vec_dot(d, o->vec1));
	rec->u = (atan2(d.x, d.z) + (M_PI)) / (2 * M_PI);
	rec->v = (d.y / o->radius);
}

void		cylinder_uv(t_object *o, t_hit *rec)
{
	t_vec	d;
	float	r;

	if (o->txt.is_txt)
	{
		r = (float)o->txt.height / (float)o->txt.width;
		d = vec_sub(rec->p, o->pos);
		d = vec_add(d, vec_pro_k(o->rot, o->txt.mv1));
		d = vec_add(d, vec_pro_k(o->rot, ((1 / o->scale / 2) / r) * o->radius));
		d = ft_rot_vec(d, o->rot, o->txt.mv2);
		d = vec(vec_dot(d, o->vec2), vec_dot(d, o->rot), vec_dot(d, o->vec1));
		rec->u = (atan2(d.x, d.z) + (M_PI)) / (2 * M_PI);
		rec->v = (d.y / o->radius) * r;
	}
	else
		cylinder_uv1(o, rec);
}

t_vec		normale_cylinder(t_object *o, t_ray *r, t_hit *rec)
{
	t_vec normale;

	normale = vec_unit(vec_sub(vec_sub(rec->p, o->pos),
				vec_pro_k(vec_unit(o->rot), vec_dot(r->dir,\
						vec_unit(o->rot)) * rec->t + vec_dot(rec->or,\
						vec_unit(o->rot)))));
	return (normale);
}

int			rt_cylinder_params(t_object *obj, t_ray *ray, t_hit *rec)
{
	rec->or = vec_sub(ray->origin, obj->pos);
	rec->a = vec_dot(ray->dir, ray->dir)\
		- pow(vec_dot(ray->dir, vec_unit(obj->rot)), 2);
	rec->b = 2 * (vec_dot(ray->dir, rec->or)\
			- (vec_dot(ray->dir, vec_unit(obj->rot))
				* vec_dot(rec->or, vec_unit(obj->rot))));
	rec->c = vec_dot(rec->or, rec->or)\
		- pow(vec_dot(rec->or, vec_unit(obj->rot)), 2)
		- obj->radius * obj->radius;
	rec->delta = rec->b * rec->b - 4.0 * rec->a * rec->c;
	if (rec->delta >= 0)
	{
		rec->t0 = (-rec->b - sqrt(rec->delta)) / (2 * rec->a);
		rec->t1 = (-rec->b + sqrt(rec->delta)) / (2 * rec->a);
		(rec->t0 > rec->t1) ? ft_float_swap(&rec->t0, &rec->t1) : 0;
		(rec->t0 <= EPS) ? ft_float_swap(&rec->t0, &rec->t1) : 0;
		return (1);
	}
	return (0);
}

int			rt_hit_cylinder(t_object *o, t_ray *ray, t_hit *record)
{
	if (rt_cylinder_params(o, ray, record))
	{
		if ((o->is_sl == 1 || o->sl_ax) && rt_slicing(o, ray, record) == 0)
			return (0);
		if (negative(record) == 0)
			return (0);
		if (record->t < record->closest && record->t >= MIN)
		{
			record->p = vec_ray(ray, record->t);
			if (record->tx == 1)
				record->n = vec_pro_k(o->sl_vec, -1);
			else if (record->is_n == 1 && record->t == record->neg[1])
				record->n = record->neg_n;
			else if (record->t1 <= EPS)
				record->n = vec_pro_k(normale_cylinder(o, ray, record), -1);
			else
				record->n = normale_cylinder(o, ray, record);
			cylinder_uv(o, record);
			if (o->txt.is_txt && o->txt.is_trans\
					&& !(trans_texture(ray, o, record)))
				return (0);
			return (1);
		}
	}
	return (0);
}
