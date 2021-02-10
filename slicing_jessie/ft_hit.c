/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 03:55:54 by belhatho          #+#    #+#             */
/*   Updated: 2020/12/09 03:55:56 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			ft_set_coef(t_object *o)
{
	o->ka = 0.4;
	o->kd = 0.6;
	o->ks = 0.6;
	o->shininess = 90;
}

int				ft_hit(t_object *o, t_ray r, t_record *rec, double tmax)
{
	int			hit_anything;

	hit_anything = 0;
	rec->closest = tmax;
	while (o)
	{
		if (o->hit(o, &r, rec))
		{
			hit_anything = 1;
			rec->closest = rec->t;
			rec->curr_obj = o;
			rec->ray = &r;
		}
		o = o->next;
	}
	return (hit_anything);
}
