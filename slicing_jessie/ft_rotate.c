/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 23:26:44 by belhatho          #+#    #+#             */
/*   Updated: 2020/11/22 23:26:54 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec		ft_rot_x(t_vec old, double theta)
{
	t_vec	new;

	new.e1 = old.e1;
	new.e2 = old.e2 * cos(theta) - old.e3 * sin(theta);
	new.e3 = old.e2 * sin(theta) + old.e3 * cos(theta);
	return (new);
}

t_vec		ft_rot_y(t_vec old, double theta)
{
	t_vec	new;

	new.e1 = old.e1 * cos(theta) + old.e3 * sin(theta);
	new.e2 = old.e2;
	new.e3 = -old.e1 * sin(theta) + old.e3 * cos(theta);
	return (new);
}

t_vec		ft_rot_z(t_vec old, double theta)
{
	t_vec	new;

	new.e1 = old.e1 * cos(theta) - old.e2 * sin(theta);
	new.e2 = old.e1 * sin(theta) + old.e2 * cos(theta);
	new.e3 = old.e3;
	return (new);
}
