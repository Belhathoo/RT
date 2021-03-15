/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hit_parabole1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saghrous <saghrous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:09:01 by saghrous          #+#    #+#             */
/*   Updated: 2021/03/15 15:17:48 by saghrous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vec			rt_parabol_normal(t_hit *rec, t_object *obj)
{
	t_vec		normal;

	normal = vec_sub(vec_sub(rec->p, obj->pos),
			vec_pro_k(obj->dir, vec_dot(vec_sub(rec->p,
					obj->pos), obj->dir) + obj->radius));
	return (vec_unit(normal));
}

static int		rt_check_parab(double c[3], t_hit *rec)
{
	double		s[2];
	int			i;
	int			num;
	double		min_sol;

	rec->t = rec->closest;
	i = -1;
	if ((num = rt_solve_quadric(c, s)))
	{
		while (++i < num)
		{
			if (s[i] >= MIN && s[i] < rec->t)
				min_sol = s[i];
		}
		if (min_sol >= MIN && min_sol < rec->closest)
		{
			rec->t = min_sol;
			return (1);
		}
	}
	return (0);
}

double			rt_init_params(t_object *obj, t_ray *ray, t_hit *record)
{
	double		c[3];
	double		a;
	double		b;

	record->or = vec_sub(ray->origin, obj->pos);
	a = vec_dot(ray->dir, obj->dir);
	b = vec_dot(record->or, obj->dir);
	c[2] = vec_dot(ray->dir, ray->dir) - a * a;
	c[1] = 2 * (vec_dot(ray->dir, record->or) - (a * (b + 2 * obj->radius)));
	c[0] = vec_dot(record->or, record->or) - b * (b + 4 * obj->radius);
	return (rt_check_parab(c, record));
}

int				rt_hit_parabol(t_object *obj, t_ray *ray, t_hit *record)
{
	if (rt_init_params(obj, ray, record))
	{
		record->p = vec_ray(ray, record->t);
		record->n = rt_parabol_normal(record, obj);
		return (1);
	}
	return (0);
}
