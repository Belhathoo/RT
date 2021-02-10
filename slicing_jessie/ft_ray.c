/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 04:21:47 by belhatho          #+#    #+#             */
/*   Updated: 2020/12/28 16:32:49 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray		ft_ray(t_vec a, t_vec b)
{
	t_ray	r;

	r.origin = a;
	r.dir = b;
	return (r);
}

t_vec		ray_fctn(t_ray *r, float t)
{
	t_vec	res;

	res = ft_plus(r->origin, (ft_pro_k(r->dir, t)));
	return (res);
}

t_ray		ft_ray_tracer(t_ptr *p, double x, double y)
{
	t_cam	cam;
	t_ray	r;

	cam = p->scene->camera;
	r.dir = ft_plus(ft_pro_k(cam.horizontal, x / IMG_WIDTH),
			ft_pro_k(cam.vertical, y / IMG_HEIGHT));
	r.dir = ft_plus(ft_minus(cam.lower_left_corner, cam.origin), r.dir);
	r.origin = cam.origin;
	return (r);
}
