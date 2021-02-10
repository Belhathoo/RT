/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shading.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 02:10:19 by belhatho          #+#    #+#             */
/*   Updated: 2020/12/09 02:11:47 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				ft_shading(t_thread *th, t_vec lo)
{
	t_ray		sh_r;
	t_record	rec;
	t_object	*o;
	double		closest;

	o = th->p->scene->obj;
	sh_r = ft_ray(th->rec.p, lo);
	closest = ft_length(sh_r.dir);
	sh_r.dir = ft_unit_vec(sh_r.dir);
	while (o != NULL)
	{
		if (o != th->rec.curr_obj)
			if (ft_hit(o, sh_r, &rec, closest))
				return (1);
		o = o->next;
	}
	return (0);
}

void			ft_ambient(t_light *l, t_thread *th, t_vec *col)
{
	t_object	*o;
	double		ia;

	o = th->rec.curr_obj;
	ia = o->ka * th->p->scene->amb;
	if (!l)
		*col = ft_pro_k(o->color, o->ka);
	else
		*col = ft_pro_k(ft_produit(th->p->scene->light->color, o->color), ia);
}
