/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:30:38 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/15 17:31:15 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	rt_init_negative(t_hit *rec)
{
	rec->neg[0] = 0;
	rec->neg[1] = 0;
	rec->neg_n = (t_vec){0, 0, 0};
}

int		rt_hit(t_scene *scene, t_ray *r, t_hit *rec, double closest)
{
	t_object	*o;
	int			check_hit;
	t_hit		record;

	if (scene->is_neg == 0)
		rt_init_negative(&record);
	else
		scene->n_obj.hit(&scene->n_obj, r, &record);
	check_hit = 0;
	o = scene->object;
	record.closest = closest;
	record.curr_obj = NULL;
	while (o)
	{
		if (o->hit(o, r, &record))
		{
			check_hit = 1;
			record.closest = record.t;
			rec->closest = record.closest;
			rec->curr_obj = o;
			rec->t = record.t;
			rec->t0 = record.t0;
			rec->t1 = record.t1;
			rec->ray = r;

			rec->p = record.p;
			rec->n = record.n;
			rec->u = record.u;
			rec->v = record.v;

			rec->tx = record.tx;
			rec->is_n = record.is_n;
			rec->neg[0] = record.neg[0];
			rec->neg[1] = record.neg[1];
			rec->neg_n = record.neg_n;
		}
		o = o->next;
	}
	return (check_hit);
}

