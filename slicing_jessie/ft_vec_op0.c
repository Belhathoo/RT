/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_op0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 02:02:47 by belhatho          #+#    #+#             */
/*   Updated: 2020/12/09 02:03:00 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	ft_div(t_vec a, t_vec b)
{
	return (ft_vec(a.e1 / b.e1, a.e2 / b.e2, a.e3 / b.e3));
}

t_vec	ft_div_k(t_vec a, double k)
{
	return (ft_vec(a.e1 / k, a.e2 / k, a.e3 / k));
}

t_vec	ft_produit(t_vec a, t_vec b)
{
	return (ft_vec(a.e1 * b.e1, a.e2 * b.e2, a.e3 * b.e3));
}

t_vec	ft_pro_k(t_vec a, double k)
{
	return (ft_vec(a.e1 * k, a.e2 * k, a.e3 * k));
}
