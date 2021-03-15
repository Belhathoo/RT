/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils_annx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:39:03 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/15 18:39:17 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

double		radtodeg(double angle)
{
	return ((angle * 180) / M_PI);
}

double		degtorad(double angle)
{
	return ((angle * M_PI) / 180);
}

int			rt_ax_parse(char *val, t_object *o, t_rt *rt)
{
	if (!ft_strcmp(val, "x") || !ft_strcmp(val, "X"))
		return (1);
	else if (!ft_strcmp(val, "y") || !ft_strcmp(val, "Y"))
		return (2);
	else if (!ft_strcmp(val, "z") || !ft_strcmp(val, "Z"))
		return (3);
	else
		rt_exit(rt, o->name, ": slice_ax should be X | Y | Z."\
				, EXIT_FAILURE);
	return (-1);
}

int			rt_uv_txt(t_object *o, double *u, double *v)
{
	*u *= o->scale;
	*v *= o->scale;
	if (o->txt.repet_txt)
	{
		*u = rt_frac(*u);
		*v = rt_frac(*v);
	}
	else
	{
		if (*u > 1 || *u < 0)
			return (1);
		if (*v > 1 || *v < 0)
			return (1);
	}
	return (0);
}

void		check_voronoi(t_cell *tmp, t_cell *cell)
{
	tmp->tocenter = vec_pro_k(vec_add(cell->toclosest, tmp->toclosest), 0.5);
	tmp->celldifference = vec_unit(vec_sub(tmp->toclosest, cell->toclosest));
	tmp->edgedistance = vec_dot(tmp->tocenter, tmp->celldifference);
	tmp->minedgedistance = fmin(cell->minedgedistance, tmp->edgedistance);
}
