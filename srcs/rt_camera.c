/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:50:46 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/11 16:50:47 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int				is_equaly(t_vec b)
{
	if ((float)b.y <= 1.0001 && (float)b.y >= 0.9999 && (float)b.x <= 0.000001\
		&& (float)b.x >= -0.000001 && (float)b.z <= 0.000001\
					&& (float)b.z >= -0.000001)
		return (1);
	if ((float)b.y >= -1.0001 && (float)b.y <= -0.9999\
		&& (float)b.x <= 0.000001 && (float)b.x >= -0.000001\
			&& (float)b.z <= 0.000001 && (float)b.z >= -0.000001)
		return (-1);
	return (0);
}

void			rt_uv_cam(t_vec w, t_vec *u, t_vec *v)
{
	t_vec	vup;

	vup = vec(0.0, 1.0, 0.0);
	if (is_equaly(w) == 1)
		vup = vec(0.0, 0.0, 1.0);
	else if (is_equaly(w) == -1)
		vup = vec(0.0, 0.0, 1.0);
	*u = vec_cross(w, vup);
	*v = vec_cross(*u, w);
	*u = vec_unit(*u);
	*v = vec_unit(*v);
}

t_camera		rt_init_camera(t_vec lookfrom, t_vec lookat, double vfov)
{
	t_camera	c;

	c.w = vec_unit(vec_sub(lookat, lookfrom));
	rt_uv_cam(c.w, &c.u, &c.v);
	c.half_h = tan((vfov * M_PI / 180.0) / 2.0);
	c.half_w = (IMG_WIDTH / IMG_HEIGHT) * c.half_h;
	c.origin = lookfrom;
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
	while (tag->attr)
	{
		if (!ft_strcmp(tag->attr->name, "lookat"))
			cam.lookat = rt_ctovec(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "lookfrom"))
			cam.lookfrom = rt_ctovec(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "fov"))
			cam.fov = rt_ctod(tag->attr->value, rt);
		tag->attr = tag->attr->next;
	}
	rt_check_cam(cam, rt);
	rt->scene->cam = rt_init_camera(cam.lookfrom, cam.lookat, cam.fov);
}
