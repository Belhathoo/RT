/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hit_objs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 23:33:48 by belhatho          #+#    #+#             */
/*   Updated: 2021/02/10 15:13:05 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "rtv1.h"
# include<rt.h>
#define decoup_opt 1

void		ft_float_swap(double *a, double *b)
{
	double	tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int			ft_hit_disque(t_object *o, t_ray *r, t_hit *rec)
{
	t_vec centre = o->pos;
	t_vec normal = o->rot;
	rec->t = ((vec_dot(normal, centre) - vec_dot(normal, r->origin)) / vec_dot(normal, r->dir));
	if (rec->t >= rec->closest || rec->t <= MIN)
		return (0);
	t_vec point = vec_sub(vec_ray(r, rec->t),centre);

	if (vec_lengthsquared(point) >= o->size)
		return(0);
	rec->n = o->rot;
	/*
		 //// cross  n with r.dir 
		arcos(dot / lnght0 * length1) 
		theta = arcos (dot(n, r.dir)) [0-180] // normalser n et r.dir
		if n * r.dir > 0 ? n = n : n = -n
	*/
	rec->p = vec_ray(r, rec->t);
	return (1);
}

int			rt_slicing(t_object *o, t_ray *r, t_hit *rec)
{
	/*
		slicing for (sphere / cylinder / )
	*/

	t_vec my = vec_unit(vec_sub(rec->p, vec_add(o->pos, 0.5)));
	t_vec ax = vec_unit(vec(0, -1, 1));//
	t_object plan;
	
	if (vec_dot(my, ax) <= 0)
	{
		plan.pos = o->pos;
		plan.rot = vec_pro_k(ax, -1);
		rec->t = rec->t1;
		rec->p = vec_ray(r, rec->t);
		my = vec_unit(vec_sub(rec->p, o->pos));
		if (vec_dot(my, ax) <= 0)
			return(0);
		return(ft_hit_plan(&plan, r, rec));//remove this line if you want an empty slice
	}
	return (1);
}

int			ft_hit_sphere(t_object *sphere, t_ray *r, t_hit *rec)
{
	rec->or = vec_sub(r->origin, sphere->pos);
	rec->coef[0] = vec_dot(r->dir, r->dir);
	rec->coef[1] = 2 * vec_dot(rec->or, r->dir);
	rec->coef[2] = vec_dot(rec->or, rec->or) - pow(sphere->size, 2);
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta > 0)
	{
		rec->t0 = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
		rec->t1 = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
		(rec->t0 < rec->t1) ? 0 : ft_float_swap(&rec->t0, &rec->t1);
		if (rec->t0 < rec->closest && rec->t0 > MIN)
		{
			rec->t = rec->t0;
			rec->p = vec_ray(r, rec->t);
			rec->n = vec_div_k(vec_sub(rec->p, sphere->pos), sphere->size);
			if (/*o.slice = 1 && */rt_slicing(sphere, r, rec) == 0)
				return 0;
			return (1);
		}
	}
	return (0);
}


int			ft_hit_plan(t_object *o, t_ray *r, t_hit *rec)
{
	rec->t = ((vec_dot(o->rot, o->pos) - vec_dot(o->rot, r->origin))
			/ vec_dot(o->rot, r->dir));
	if (rec->t >= rec->closest || rec->t <= MIN)
		return (0);
	rec->n = o->rot;
	rec->p = vec_ray(r, rec->t);
	return (1);
}


int			ft_hit_cylinder(t_object *o, t_ray *r, t_hit *rec)
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
		(rec->t0 < rec->t1) ? 0 : ft_float_swap(&rec->t0, &rec->t1);
		if (rec->t0 < rec->closest && rec->t0 > MIN)
		{
			rec->p = vec_ray(r, rec->t);
			rec->n = vec_unit(vec_sub(vec_sub(rec->p, o->pos), vec_pro_k(o->rot, vec_dot(r->dir, o->rot) * rec->t + vec_dot(rec->or, o->rot))));
			if (rt_slicing(o, r, rec) == 0) // o.sli = 1
				return (0);
			return (1);
		}
	}
	return (0);
	
}



int			ft_hit_cone(t_object *o, t_ray *r, t_hit *rec)
{
	rec->or = vec_sub(r->origin, o->pos);
	rec->coef[0] = vec_dot(r->dir, r->dir) - (1 + pow(tan(o->size), 2))
		* pow(vec_dot(r->dir, o->rot), 2);
	rec->coef[1] = 2 * (vec_dot(r->dir, rec->or) - (1 + pow(tan(o->size), 2))
			* vec_dot(r->dir, o->rot) * vec_dot(rec->or, o->rot));
	rec->coef[2] = vec_dot(rec->or, rec->or) - (1 + pow(tan(o->size), 2))
		* pow(vec_dot(rec->or, o->rot), 2);
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta < 0)
		return (0);
	rec->t0 = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
	rec->t1 = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
	rec->t0 = (rec->t0 > MIN && rec->t0 < rec->t1) ?
					rec->t0 : rec->t1;
	if (rec->t0 < rec->closest && rec->t0 > MIN)
	{
		rec->t = rec->t0;
		rec->p = vec_ray(r, rec->t);
		rec->tmp = vec_pro_k(o->rot, (vec_dot(r->dir, o->rot) * rec->t
					+ vec_dot(rec->or, o->rot)));
		rec->tmp = vec_pro_k(rec->tmp, (1 + pow(tan(o->size), 2)));
		rec->n = vec_unit(vec_sub(vec_sub(rec->p, o->pos), rec->tmp));
		return (1);
	}
	return (0);
}
