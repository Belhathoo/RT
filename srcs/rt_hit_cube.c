/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hit_cube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:45:01 by ibel-kha          #+#    #+#             */
/*   Updated: 2021/03/11 18:47:22 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int		rt_hit_cube(t_object *o, t_ray *r, t_hit *rec)
{
	int			check_hit;
	t_hit		record;

	check_hit = 0;
	record.closest = rec->closest;
	record.curr_obj = NULL;
	while (o->compos)
	{
		if (o->compos->hit(o->compos, r, &record))
		{
			check_hit = 1;
			record.closest = record.t;
			rec->closest = record.closest;
			rec->t = record.t;
			rec->p = record.p;
			rec->n = record.n;
			rec->u = record.u;
			rec->v = record.v;
			rec->curr_obj = o;
			rec->ray = r;
		}
		o = o->compos;
	}
	return (check_hit);
}
