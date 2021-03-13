/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hit_lcylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:53:01 by msoulaim          #+#    #+#             */
/*   Updated: 2021/03/13 19:01:27 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		rt_lcylinder_params(t_object *obj, t_ray *ray, t_hit *rec)
{
	rec->or = vec_sub(ray->origin, obj->pos);
	rec->a = vec_dot(ray->dir, ray->dir) -
	pow(vec_dot(ray->dir, vec_unit(obj->rot)), 2);
	rec->b = 2 * (vec_dot(ray->dir, rec->or) -
	(vec_dot(ray->dir, vec_unit(obj->rot))
	* vec_dot(rec->or, vec_unit(obj->rot))));
	rec->c = vec_dot(rec->or, rec->or) -
	pow(vec_dot(rec->or, vec_unit(obj->rot)), 2)
		- obj->radius * obj->radius;
	rec->delta = rec->b * rec->b - 4.0 * rec->a * rec->c;
}

void		rt_lcy_sol(t_hit *rec)
{
	rec->t0 = (-rec->b - sqrt(rec->delta)) / (2 * rec->a);
	rec->t1 = (-rec->b + sqrt(rec->delta)) / (2 * rec->a);
	(rec->t0 < rec->t1) ? 0 : ft_float_swap(&rec->t0, &rec->t1);
	(rec->t0 <= EPS) ? ft_float_swap(&rec->t0, &rec->t1) : 0;
}

void		rt_lcyl_hitted(t_object *obj, t_ray *ray, t_hit *rec)
{
	rec->p = vec_ray(ray, rec->t);
	rec->n = normale_cylinder(obj, ray, rec);
	rec->n = (rec->t0 > rec->t1) ? vec_pro_k(rec->n, -1) : rec->n;
	cylinder_uv(obj, rec);
}

int			rt_hit_lcylinder(t_object *obj, t_ray *ray, t_hit *rec)
{
	double m;

	rt_lcylinder_params(obj, ray, rec);
	if (rec->delta >= 0)
	{
		rt_lcy_sol(rec);
		m = vec_dot(ray->dir, obj->rot) * rec->t0 + vec_dot(rec->or, obj->rot);
		if (m <= -obj->height / 2 || m >= obj->height / 2)
		{
			m = vec_dot(ray->dir, obj->rot) *
			rec->t1 + vec_dot(rec->or, obj->rot);
			if (m <= -obj->height / 2 || m >= obj->height / 2)
				return (0);
			ft_float_swap(&rec->t0, &rec->t1);
		}
		rec->t = rec->t0;
		if (rec->t < rec->closest && rec->t >= EPS)
		{
			rt_lcyl_hitted(obj, ray, rec);
			return (1);
		}
	}
	return (0);
}
