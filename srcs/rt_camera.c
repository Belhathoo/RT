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

# include <rt.h>

int		is_yequal(t_vec a, t_vec b)
{
	if ((float)a.y == (float)b.y )// < (float)0.01)
		return (1);
	if ((float)a.y == -(float)b.y) //< (float)0.01)
		return (-1);
	return (0);
}

void			rt_uv_cam(t_vec w, t_vec *u, t_vec *v)
{
	t_vec	vup;

	vup = vec_unit(vec(0.0, 1.0, 0.0));
	if (is_yequal(vup, w) == 1)
	{
		ft_putendl("ll");
		*u = vec(-1.0, 0.0, 0.0);
		*v = vec(0.0, 0.0, 1.0);
	}
	else
	{
		if (is_yequal(vup, w) == -1)
		{
		ft_putendl("-ll");
			*u = vec(1.0, 0.0, 0.0);
			*v = vec(0.0, 0.0, 1.0);

		}
		else
		{
		ft_putendl("no");
			*u = vec_cross(w, vup);
			*v = vec_cross(*u, w);
		}
	}
}

t_camera		rt_init_camera(t_vec lookfrom, t_vec lookat, double vfov)
{
	t_camera	c;
	// printf("%.2f %.2f %.2f\n", lookfrom.x,lookfrom.y ,lookfrom.z);

	c.w = vec_unit(vec_sub(lookat, lookfrom));
	rt_uv_cam(c.w, &c.u, &c.v);
	printf("w. %.2f %.2f %.2f\n", c.w.x,c.w.y ,c.w.z);
	printf("u. %.2f %.2f %.2f\n", c.u.x,c.u.y ,c.u.z);
	// c.u = vec_unit(vec_cross(c.w, vup));
	// c.v = vec_cross(c.u, c.w);
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
		// printf("%.2f %.2f %.2f\n", cam.lookfrom.x,cam.lookfrom.y ,cam.lookfrom.z);

	rt_check_cam(cam, rt);
	rt->scene->cam = rt_init_camera(cam.lookfrom, cam.lookat, cam.fov);
}
