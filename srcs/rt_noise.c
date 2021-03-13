/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_noise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:47:35 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/13 18:47:41 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vec		rt_noise_damier(t_hit *rec)
{
	int pro1;
	int pro2;

	if (ft_strcmp(rec->curr_obj->name, "torus") == 0)
		return (rt_torus_noise(rec));
	pro1 = floor(rec->u * rec->curr_obj->scale);
	pro2 = floor(rec->v * rec->curr_obj->scale);
	if (fabs(fmod(pro1, 2)) == fabs(fmod(pro2, 2)))
		return (rec->curr_obj->noi.col1);
	return (rec->curr_obj->noi.col2);
}

t_vec		rt_noise_circles(t_object *o, t_hit *rec)
{
	double		pro;
	t_vec		r_p;

	r_p = vec_pro_k(vec_sub(o->pos, rec->p), o->scale);
	pro = floor(vec_length(r_p));
	if (fmod(pro, 2) == 0.0)
		return (rec->curr_obj->noi.col1);
	else
		return (rec->curr_obj->noi.col2);
}

t_vec		rt_noise_voronoi(t_hit *rec, t_object *o)
{
	t_vec	r_p;

	r_p = vec_sub(rec->p, o->pos);
	r_p = vec(vec_dot(r_p, o->vec1), vec_dot(r_p, o->vec2)\
				, vec_dot(r_p, o->rot));
	return (rt_voronoi(r_p, o));
}

t_vec		rt_noise(t_rt *rt, t_object *o, t_hit *rec)
{
	t_vec	ret;
	int		type;
	t_vec	p;

	p = vec_sub(o->pos, rec->p);
	p = vec(vec_dot(p, o->vec1), vec_dot(p, o->vec2), \
			vec_dot(p, o->rot));
	type = o->noi.type;
	ret = o->noi.col1;
	if (type == DAMIER)
		return (rt_noise_damier(rec));
	else if (type == CIRCLES)
		return (rt_noise_circles(o, rec));
	else if (type == VORONOI1 || type == VORONOI2 \
			|| type == VORONOI3)
		return (rt_noise_voronoi(rec, o));
	else if (type == PERLIN)
		return (perlin(rt, p, o));
	return (ret);
}
