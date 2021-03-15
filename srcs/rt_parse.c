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
		xml_exit(x, "", "One Camera !!", EXIT_FAILURE);
	while (x->tags)
	{
		if (!ft_strcmp(x->tags->name, "Camera"))
			rt_add_camera(x->tags, rt);
		else if (!ft_strcmp(x->tags->name, "Object"))
			rt_add_object(x->tags, rt);
		else if (!ft_strcmp(x->tags->name, "Neg_Object"))
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
		xml_exit(x, " tags", " < / >", EXIT_FAILURE);
	xml_to_rt(x, rt);
	
	xml_close(x);
	if (rt->is_perlin)
		init_perlin(rt);
	rt->name_sc = argv[1];
}