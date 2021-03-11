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

t_camera		rt_init_camera(t_vec lookfrom, t_vec lookat, double vfov)
{
	t_camera	c;
	t_vec		vup;
	t_vec		tmp;

	tmp = vec_unit(vec_sub(lookat, lookfrom));
	vup = vec_unit(vec(0.0, 1.0, 0.0));
	if (!(vec_dot(vec_cross(tmp, vup), vec3(1.0))))
		vup = vec(0.0, 0.0, 1.0);
	c.half_h = tan((vfov * M_PI / 180.0) / 2.0);
	c.half_w = (IMG_WIDTH / IMG_HEIGHT) * c.half_h;
	c.origin = lookfrom;
	c.w = vec_unit(vec_sub(lookat, lookfrom));
	c.u = vec_unit(vec_cross(c.w, vup));
	c.v = vec_cross(c.u, c.w);
	c.lower_left_corner = vec_sub(c.origin, vec_add(vec_pro_k(c.v, c.half_h),
				vec_pro_k(c.u, c.half_w)));
	c.lower_left_corner = vec_add(c.lower_left_corner, c.w);
	c.horizontal = vec_pro_k(c.u, 2.0 * c.half_w);
	c.vertical = vec_pro_k(c.v, 2.0 * c.half_h);
	c.fov = vfov;
	c.lookat = lookat;
	c.lookfrom = lookfrom;
	return (c);
}

void			rt_add_camera(t_tag *tag, t_rt *rt)
{
	t_camera	cam;

	cam.lookfrom = vec(0.0, 10.0, 20.0);
	cam.lookat = vec(0.0, 0.0, 0.0);
	cam.fov = 60;
	while (TA)
	{
		if (!ft_strcmp(TA->name, "lookat"))
			cam.lookat = rt_ctovec(TA->value, rt);
		else if (!ft_strcmp(TA->name, "lookfrom"))
			cam.lookfrom = rt_ctovec(TA->value, rt);
		else if (!ft_strcmp(TA->name, "fov"))
			cam.fov = rt_ctod(TA->value, rt);
		TA = TA->next;
	}
	rt_check_cam(cam, rt);
	RS->cam = rt_init_camera(cam.lookfrom, cam.lookat, cam.fov);
}

void			xml_to_rt(t_xml *x, t_rt *rt)
{
	if (x->cam_nbr != 1)
		xml_exit(x, "One Camera !!", EXIT_FAILURE);
	/*
	obj_nbr == 0 >> with UI can add objects
	*/
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
