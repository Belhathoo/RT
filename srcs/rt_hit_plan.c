/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hit_plan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:05:46 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/07 19:05:48 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>


int      cutt_plane(t_hit *rec, t_object *o)
{
	double largeur;
	double longeur;
	t_vec   pnt;

	pnt = vec_sub(rec->p, o->pos);

	if ((fabs(vec_dot(pnt, o->vec1)) > o->width 
				|| fabs(vec_dot(pnt, vec_cross(o->rot,o->vec1))) > o->height))
		return (0);
	// else if ((fabs(vec_dot(pnt, o->vec2)) > o->width 
	// 			|| fabs(vec_dot(pnt, o->rot)) > o->height))
	// 	return (0);

	return (1);
}


void			plane_uv(t_hit *rec, t_object *o)
{
	if (o->txt.is_txt)
	{
		rec->u = rt_frac(vec_dot(vec_pro_k(vec_sub(rec->p, o->pos), o->scale), o->vec1));
		rec->v = rt_frac(vec_dot(vec_pro_k(vec_sub(rec->p, o->pos), o->scale),vec_cross(o->rot,o->vec1)));
	}
	else 
	{
		rec->u = rt_frac(vec_dot(vec_sub(rec->p, o->pos), o->vec2));
		rec->v = rt_frac(vec_dot(vec_sub(rec->p, o->pos), o->vec1));

	}
}

int     rt_hit_plan(t_object *o, t_ray *r, t_hit *rec)
{
	double  t;

	t = ((vec_dot(o->rot, o->pos) - vec_dot(o->rot, r->origin))
			/ vec_dot(o->rot, r->dir));
	if ( t > rec->closest || t <= EPS)
		return (0);
	rec->t = t;
	if (rec->negative[0] <= rec->t && rec->t <= rec->negative[1])
		return (0);
	rec->p = vec_ray(r, rec->t);
	rec->n = vec_dot(r->dir, o->rot) > 0 ? vec_pro_k(o->rot, -1) : o->rot;
	plane_uv(rec, o);
	return (1);
}

int         rt_hit_care(t_object *o, t_ray *ray, t_hit *rec)
{
	double  t;

	rec->t = ((vec_dot(o->rot, o->pos) - vec_dot(o->rot, ray->origin))
			/ vec_dot(o->rot, ray->dir));
	if (rec->t >= MIN && rec->t < rec->closest)
	{
		rec->p = vec_ray(ray, rec->t);
		if (cutt_plane(rec, o) == 0)
			return (0);
		rec->n = vec_dot(ray->dir, o->rot) > 0 ? vec_pro_k(o->rot, -1) : o->rot;
		plane_uv(rec, o);
		return (1);
	}
	return (0);
}
