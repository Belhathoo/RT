/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hit_disc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:32:38 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/15 17:32:45 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int			rt_hit_disc(t_object *o, t_ray *r, t_hit *rec)
{
	t_vec centre;
	t_vec point;

	centre = o->pos;
	rec->t = ((vec_dot(o->rot, o->pos) - vec_dot(o->rot, r->origin))
			/ vec_dot(o->rot, r->dir));
	point = vec_sub(vec_ray(r, rec->t), centre);
	if (rec->t > rec->closest || rec->t <= EPS)
		return (0);
	if (vec_length(point) >= o->radius)
		return (0);
	rec->p = vec_ray(r, rec->t);
	rec->n = vec_dot(r->dir, o->rot) > 0 ? vec_pro_k(o->rot, -1) : o->rot;
	plane_uv(rec, o);
	if (o->txt.is_txt && o->txt.is_trans && !(trans_texture(r, o, rec)))
		return (0);
	return (1);
}
