/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_noise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 16:02:05 by belhatho          #+#    #+#             */
/*   Updated: 2021/02/18 16:02:17 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <rt.h>

t_noise		rt_add_noise(char *val, t_rt *rt) //parser
{
	t_noise	n;

	if (!ft_strcmp(val, "damier"))
		n.type = 0;
	else if (!ft_strcmp(val, "00"))
		n.type = 1;
	else if (!ft_strcmp(val, "00"))
		n.type = 2;
	else
		rt_exit(rt, "noise: Uknown type!", EXIT_FAILURE);
	n.is_noise = 1;
	return (n);
}

t_vec	rt_noise(t_object *o, t_hit rec)
{
	t_vec	ret;

	ret = vec (0.0, 0.0, 1.0);
	if (o->noi.type == 0)
		return (rt_txt_damier(&rec));
	return (ret);
}
