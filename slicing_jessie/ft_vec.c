/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 04:22:30 by belhatho          #+#    #+#             */
/*   Updated: 2020/12/09 04:22:32 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./rtv1.h"

t_vec		ft_vec(double x, double y, double z)
{
	t_vec	v;

	v.e1 = x;
	v.e2 = y;
	v.e3 = z;
	return (v);
}

t_vec		ft_unit_vec(t_vec a)
{
	double	k;

	if (a.e1 == 0.0 && a.e2 == 0.0 && a.e3 == 0.0)
		return (ft_vec(0, 0, 0));
	k = 1.0 / sqrt(a.e1 * a.e1 + a.e2 * a.e2 + a.e3 * a.e3);
	return (ft_pro_k(a, k));
}

double		ft_length(t_vec a)
{
	return (sqrt(a.e1 * a.e1 + a.e2 * a.e2 + a.e3 * a.e3));
}

double		ft_lengthsquared(t_vec a)
{
	return (a.e1 * a.e1 + a.e2 * a.e2 + a.e3 * a.e3);
}
