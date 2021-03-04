/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_negatives.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:36:16 by msoulaim          #+#    #+#             */
/*   Updated: 2021/03/03 17:46:26 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int		negative(t_hit *record)
{
	record->is_n = 0;
	if ((record->t0 <= record->negative[0] || record->t0 >= record->negative[1]))
		record->t = record->t0;
	else if (record->negative[0] <= record->t0 && record->t0 <= record->negative[1] && record->negative[1] < record->t1)
	{
		record->is_n = 1;
		record->t = record->negative[1];
	}
	else
		return 0;
	return (1);
}

int			rt_negative_sphere(t_object *sphere, t_ray *r, t_hit *rec)
{
	t_vec tmp;

	rec->or = vec_sub(r->origin, sphere->pos);
	rec->coef[0] = vec_dot(r->dir, r->dir);
	rec->coef[1] = 2 * vec_dot(rec->or, r->dir);
	rec->coef[2] = vec_dot(rec->or, rec->or) - pow(sphere->size, 2);
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta > 0)
	{
		rec->negative[0] = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
		rec->negative[1] = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
		(rec->negative[0] > rec->negative[1]) ? ft_float_swap(&rec->negative[0], &rec->negative[1]) : 0;
		tmp = vec_ray(r, rec->negative[1]);
		rec->negative_normal = vec_div_k(vec_sub(tmp, sphere->pos), -sphere->size);
	}
	else
	{
		rec->negative[0] = 0;
		rec->negative[1] = 0;
		rec->negative_normal = (t_vec){0, 0, 0};
	}
	return (0);
}

int			rt_negative_cylinder(t_object *o, t_ray *r, t_hit *rec)
{
	rec->or = vec_sub(r->origin, o->pos);
	rec->coef[0] = vec_dot(r->dir, r->dir) - pow(vec_dot(r->dir, o->rot), 2);
	rec->coef[1] = 2 * (vec_dot(r->dir, rec->or) - (vec_dot(r->dir, o->rot)
				* vec_dot(rec->or, o->rot)));
	rec->coef[2] = vec_dot(rec->or, rec->or) - pow(vec_dot(rec->or, o->rot), 2)
		- o->size * o->size;
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta >= 0)
	{
		rec->t0 = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
		rec->t1 = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
		(rec->t0 > rec->t1) ? ft_float_swap(&rec->t0, &rec->t1) : 0;
		rec->negative[0] = rec->t0;
		rec->negative[1] = rec->t1;
		rec->p = vec_ray(r, rec->negative[1]);
		rec->negative_normal = vec_unit(vec_sub(vec_sub(rec->p, o->pos), vec_pro_k(o->rot, vec_dot(r->dir, o->rot) * rec->t + vec_dot(rec->or, o->rot))));
		rec->negative_normal = vec_pro_k(rec->negative_normal, -1);
	}
	else
	{
		rec->negative[0] = 0;
		rec->negative[1] = 0;
		rec->negative_normal = (t_vec){0, 0, 0};
	}
	return (0);
}

int			rt_negative_cone(t_object *o, t_ray *r, t_hit *rec)
{
	t_vec tmp;

	rec->or = vec_sub(r->origin, o->pos);
	rec->coef[0] = vec_dot(r->dir, r->dir) - ((1 + pow(tan(o->size), 2))
		* pow(vec_dot(r->dir, o->rot), 2));
	rec->coef[1] = 2 * (vec_dot(r->dir, rec->or) - ((1 + pow(tan(o->size), 2))
			* vec_dot(rec->or, o->rot) * vec_dot(r->dir, o->rot)));
	rec->coef[2] = vec_dot(rec->or, rec->or) - ((1 + pow(tan(o->size), 2)) // * rec->or.z * rec->or.z);
		* pow(vec_dot(rec->or, o->rot), 2));
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta > 0)
	{
		rec->negative[0] = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
		rec->negative[1] = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
		(rec->negative[0] > rec->negative[1]) ? ft_float_swap(&rec->negative[0], &rec->negative[1]) : 0;
		tmp = vec_ray(r, rec->negative[1]);
		rec->t = rec->negative[1];
		rec->negative_normal = normale_cone(o, r, rec);
		rec->negative_normal = vec_pro_k(rec->negative_normal, -1);
	}
	else
	{
		rec->negative[0] = 0;
		rec->negative[1] = 0;
		rec->negative_normal = (t_vec){0, 0, 0};
	}
	return (0);
}