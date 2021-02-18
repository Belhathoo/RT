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

t_vec  torus_noise(t_hit *rec)
{
	int i;
	int j;
    int oddity;

	i = (int)(10 * rec->u);
	j = (int)(10 * rec->v);
	if ((i & 0x01) == (j & 0x01))
		oddity = 1;
	else
		oddity = 0;
	if ((((10 * rec->u - i) < 0.2) && oddity) || ((10 * rec->v - j) < 0.2))
	  return (vec(0, 0, 0));
	else 
	  return (vec(1, 1, 1));
}

t_vec		rt_noise_damier(t_hit *rec)
{
	int pro1;
	int pro2;
	
	if (ft_strcmp(rec->curr_obj->name, "TORUS") == 0)
		return (torus_noise(rec));
	pro1 = floor(rec->u * 14);
	pro2 = floor(rec->v * 14);
	if (fabs(fmod(pro1, 2)) == fabs(fmod(pro2, 2)))
		return (vec(0, 0, 0));
	return (vec(1, 1, 1));
	
}

t_vec	rt_noise(t_object *o, t_hit rec)
{
	t_vec	ret;

	ret = vec (0.0, 0.0, 1.0);
	if (o->noi.type == 0)
		return (rt_noise_damier(&rec));
	return (ret);
}
