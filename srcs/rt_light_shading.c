/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light_shading.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:54:57 by belhatho          #+#    #+#             */
/*   Updated: 2021/02/18 15:55:03 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int				rt_shading(t_thread *th, t_vec lo)
{
	t_ray		sh_r;
	t_hit	    rec;
	t_object	*o;

	o = th->rt->scene->object;
	sh_r = rt_ray(vec_add(th->rec.p, vec_pro_k(lo, 0.001)), lo);
	rec.closest = vec_length(sh_r.dir);
	sh_r.dir = vec_unit(sh_r.dir);
	while (o != NULL)
	{
		if (o != th->rec.curr_obj)
			if (rt_hit(th->rt->scene, &sh_r, &rec))
				return (1);
		o = o->next;
	}
	return (0);
}

void			rt_ambient(t_light *l, t_thread *th, t_vec *col)
{
	t_object	*o;
	double		ia;
	t_vec		c;
     /*
	 	recheck !!
	 */
	c = vec(0.0, 0.0, 0.0);
	o = th->rec.curr_obj;
	
	ia = th->rt->scene->ambient;
	// ia *= (!l) ? 1 : l->intensity ;
	if (!l)
		*col = vec_prod(*col, vec_pro_k(o->mat.ka, ia));
	else
		*col = vec_prod(*col, vec_prod(l->col, vec_pro_k(o->mat.ka, ia)));
}
