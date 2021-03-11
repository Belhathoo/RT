/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:54:02 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/11 11:55:06 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void			xml_to_rt(t_xml *x, t_rt *rt)
{
	if (x->cam_nbr != 1)
		xml_exit(x, "One Camera !!", EXIT_FAILURE);
	// obj_nbr == 0 >> with UI can add objects
	while (x->tags)
	{
		if (!ft_strcmp(x->tags->name, "Camera"))
			rt_add_camera(x->tags, rt);
		else if (!ft_strcmp(x->tags->name, "Object"))
			rt_add_object(x->tags, rt);
		else if (!ft_strcmp(x->tags->name, "N_Object"))
			rt_add_neg_object(x->tags, rt);
		else if (!ft_strcmp(x->tags->name, "Light"))
			rt_add_light(x->tags, rt);
		else if (!ft_strcmp(x->tags->name, "Option"))
			rt_add_option(x->tags, rt);
		x->tags = x->tags->next;
	}
}

void			rt_parser(t_rt *rt, char **argv)
{
	t_xml		*x;

	x = xml_init(argv[1]);
	if (xml_parse(x) == -1)
		xml_exit(x, "-1\n", EXIT_FAILURE);
	// err. (check redo in main libxml)
	xml_to_rt(x, rt);
	// printf("%d", RS->light->type);
	rt->name_sc = argv[1];
	xml_close(x);
}


	// rt->cam.w = tan((60.0 * M_PI / 180.0) / 2.0) * 1.0;
	// rt->cam.h = rt->cam.w;
	// rt->up = normale(constrector(0.0, 1.0, 0.0));
	// rt->to = normale(soustraction(rt->cam.cam_ray.o, rt->cam.look_at));
	// if (equal(rt->up, rt->to) == 1)
	// {
	// 	rt->cam.u = constrector(1.0, 0.0, 0.0);
	// 	rt->cam.v = constrector(0.0, 0.0, 1.0);
	// }
	// else
	// {
	// 	if (equal(rt->up, rt->to) == 2)
	// 	{
	// 		rt->cam.u = constrector(-1.0, 0.0, 0.0);
	// 		rt->cam.v = constrector(0.0, 0.0, 1.0);
	// 	}
	// 	else
	// 	{
	// 		rt->cam.u = cross(rt->up, rt->to);
	// 		rt->cam.v = cross(rt->cam.u, rt->to);
	// 	}
	// }