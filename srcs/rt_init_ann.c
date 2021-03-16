/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_ann.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:32:17 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/15 15:32:18 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_light			*rt_init_light(t_rt *rt)
{
	t_light	*light;

	if (!(light = (struct s_l*)malloc(sizeof(struct s_l))))
		rt_exit(rt, "Cannot allocate\n", "", EXIT_FAILURE);
	light->type = PT_LIGHT;
	light->pos = vec(0.0, 5.0, 15.0);
	light->col = vec(1.0, 1.0, 1.0);
	light->dir = vec(0.0, -1.0, 0.0);
	light->intensity = 0.6;
	light->next = NULL;
	return (light);
}

t_texture		rt_init_txt(void)
{
	t_texture	txt;

	txt.is_txt = 1;
	txt.buf = NULL;
	txt.img = NULL;
	return (txt);
}

void			init_perlin(t_rt *rt)
{
	int i;

	if (!(rt->ran = (t_vec *)malloc(256 * sizeof(t_vec))))
		rt_exit(rt, "perlin: ", "Cannot allacte", EXIT_FAILURE);
	i = 0;
	while (i < 256)
	{
		rt->ran[i].x = rand() % 255;
		rt->ran[i].y = rand() % 255;
		rt->ran[i].z = rand() % 255;
		rt->ran[i] = vec_unit(rt->ran[i]);
		rt->hash[i] = rand() % 255;
		i++;
	}
}

t_object		rt_init_neg_object(void)
{
	t_object obj;

	obj.name = NULL;
	obj.pos = vec(0.0, 0.0, 0.0);
	obj.angle = 30.0;
	obj.radius = 2.0;
	obj.dir = vec(0.0, 1.0, 0.0);
	obj.rot = vec(0.0, 0.0, 0.0);
	obj.is_sl = 0;
	obj.txt.is_txt = 0;
	obj.noi.is_noise = 0;
	obj.next = NULL;
	obj.compos = NULL;
	return (obj);
}
