/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:25:55 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/15 18:26:10 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libvec.h>

t_vec		vec_prod(t_vec a, t_vec b)
{
	return (vec(a.x * b.x, a.y * b.y, a.z * b.z));
}

t_vec		vec_pro_k(t_vec a, double k)
{
	return (vec(a.x * k, a.y * k, a.z * k));
}

t_vec		vec_div(t_vec a, t_vec b)
{
	return (vec(a.x / b.x, a.y / b.y, a.z / b.z));
}

t_vec		vec_div_k(t_vec a, double k)
{
	if (k == 0.0)
		return (vec(0, 0, 0));
	return (vec(a.x / k, a.y / k, a.z / k));
}

t_vec		vec_add_k(t_vec a, double k)
{
	return (vec(a.x + k, a.y + k, a.z + k));
}
