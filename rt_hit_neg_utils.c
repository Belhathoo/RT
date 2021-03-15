/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hit_neg_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:56:19 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/15 18:00:24 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		aff_coef_ncone(t_hit *rec, t_object *o, t_ray *r)
{
	rec->coef[0] = vec_dot(r->dir, r->dir) - ((1 + pow(tan(o->angle), 2))
		* pow(vec_dot(r->dir, o->rot), 2));
	rec->coef[1] = 2 * (vec_dot(r->dir, rec->or) - ((1 + pow(tan(o->angle), 2))
			* vec_dot(rec->or, o->rot) * vec_dot(r->dir, o->rot)));
	rec->coef[2] = vec_dot(rec->or, rec->or) - ((1 + pow(tan(o->angle), 2))
		* pow(vec_dot(rec->or, o->rot), 2));
}

void		aff_coef_ncylinder(t_hit *rec, t_object *o, t_ray *r)
{
	rec->coef[0] = vec_dot(r->dir, r->dir) - pow(vec_dot(r->dir, o->rot), 2);
	rec->coef[1] = 2 * (vec_dot(r->dir, rec->or) - (vec_dot(r->dir, o->rot)
				* vec_dot(rec->or, o->rot)));
	rec->coef[2] = vec_dot(rec->or, rec->or) - pow(vec_dot(rec->or, o->rot), 2)
		- o->radius * o->radius;
}

