/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 01:41:21 by belhatho          #+#    #+#             */
/*   Updated: 2020/12/09 01:58:38 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	ft_plus(t_vec a, t_vec b)
{
	return (ft_vec(a.e1 + b.e1, a.e2 + b.e2, a.e3 + b.e3));
}

t_vec	ft_plus_k(t_vec a, double k)
{
	return (ft_vec(a.e1 + k, a.e2 + k, a.e3 + k));
}

t_vec	ft_minus(t_vec a, t_vec b)
{
	return (ft_vec(a.e1 - b.e1, a.e2 - b.e2, a.e3 - b.e3));
}

t_vec	ft_cross(t_vec a, t_vec b)
{
	return (ft_vec((a.e2 * b.e3 - a.e3 * b.e2), -(a.e1 * b.e3 - a.e3 * b.e1),
				(a.e1 * b.e2 - a.e2 * b.e1)));
}

double	ft_dot(t_vec a, t_vec b)
{
	return (a.e1 * b.e1 + a.e2 * b.e2 + a.e3 * b.e3);
}
