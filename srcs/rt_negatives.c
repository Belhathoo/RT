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

int			negative(t_hit *record)
{
	record->is_n = 0;
	if ((record->t0 <= record->neg[0]\
		|| record->t0 >= record->neg[1]))
		record->t = record->t0;
	else if (record->neg[0] <= record->t0\
	&& record->t0 <= record->neg[1] && record->neg[1] < record->t1)
	{
		record->is_n = 1;
		record->t = record->neg[1];
	}
	else
		return (0);
	return (1);
}

int			rt_negative_sphere(t_object *sphere, t_ray *r, t_hit *rec)
{
	t_vec tmp;

	rec->or = vec_sub(r->origin, sphere->pos);
	rec->coef[0] = vec_dot(r->dir, r->dir);
	rec->coef[1] = 2 * vec_dot(rec->or, r->dir);
	rec->coef[2] = vec_dot(rec->or, rec->or) - pow(sphere->radius, 2);
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta > 0)
	{
		rec->neg[0] = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
		rec->neg[1] = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
		if (rec->neg[0] > rec->neg[1])
			ft_float_swap(&rec->neg[0], &rec->neg[1]);
		tmp = vec_ray(r, rec->neg[1]);
		rec->neg_n = vec_div_k(vec_sub(tmp, sphere->pos)\
			, -sphere->radius);
	}
	else
	{
		rec->neg[0] = 0;
		rec->neg[1] = 0;
		rec->neg_n = (t_vec){0, 0, 0};
	}
	return (0);
}

int			rt_negative_cylinder(t_object *o, t_ray *r, t_hit *rec)
{
	rec->or = vec_sub(r->origin, o->pos);
	aff_coef_ncylinder(rec, o, r);
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta >= 0)
	{
		rec->t0 = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
		rec->t1 = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
		(rec->t0 > rec->t1) ? ft_float_swap(&rec->t0, &rec->t1) : 0;
		rec->neg[0] = rec->t0;
		rec->neg[1] = rec->t1;
		rec->p = vec_ray(r, rec->neg[1]);
		rec->neg_n = vec_unit(vec_sub(vec_sub(rec->p, o->pos)\
			, vec_pro_k(o->rot, vec_dot(r->dir, o->rot)\
			* rec->t + vec_dot(rec->or, o->rot))));
		rec->neg_n = vec_pro_k(rec->neg_n, -1);
	}
	else
	{
		rec->neg[0] = 0;
		rec->neg[1] = 0;
		rec->neg_n = (t_vec){0, 0, 0};
	}
	return (0);
}

int			rt_negative_cone(t_object *o, t_ray *r, t_hit *rec)
{
	t_vec tmp;

	rec->or = vec_sub(r->origin, o->pos);
	aff_coef_ncone(rec, o, r);
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta > 0)
	{
		rec->neg[0] = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
		rec->neg[1] = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
		(rec->neg[0] > rec->neg[1]) ?\
					ft_float_swap(&rec->neg[0], &rec->neg[1]) : 0;
		tmp = vec_ray(r, rec->neg[1]);
		rec->t = rec->neg[1];
		rec->neg_n = normale_cone(o, r, rec);
		rec->neg_n = vec_pro_k(rec->neg_n, -1);
	}
	else
	{
		rec->neg[0] = 0;
		rec->neg[1] = 0;
		rec->neg_n = (t_vec){0, 0, 0};
	}
	return (0);
}
