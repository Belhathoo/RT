/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_noise_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:49:23 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/13 18:49:28 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int			rt_add_noise(char *val, t_rt *rt)
{
	if (!ft_strcmp(val, "damier"))
		return (0);
	else if (!ft_strcmp(val, "circles"))
		return (1);
	else if (!ft_strcmp(val, "voronoi1"))
		return (2);
	else if (!ft_strcmp(val, "voronoi2"))
		return (3);
	else if (!ft_strcmp(val, "voronoi3"))
		return (4);
	else if (!ft_strcmp(val, "perlin") && (rt->is_perlin = 1))
		return (5);
	rt_exit(rt, val, ": noise: unknown type.", EXIT_FAILURE);
	return (-1);
}

t_vec		rt_torus_noise(t_hit *rec)
{
	int			i;
	int			j;
	int			oddity;

	i = (int)(10 * rec->u);
	j = (int)(10 * rec->v);
	if ((i & 0x01) == (j & 0x01))
		oddity = 1;
	else
		oddity = 0;
	if ((((10 * rec->v - i) < 0.2) && oddity) || ((10 * rec->v - j) < 0.2))
		return (vec(0, 0, 0));
	else
		return (vec(1, 1, 1));
}
