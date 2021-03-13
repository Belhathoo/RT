/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_anati_aliasing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:25:21 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/11 15:33:16 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		rt_init_stereo(t_rt *rt)
{
	rt->scene->camm[0] = rt_init_camera(vec_add(rt->scene->cam.lookfrom\
			, vec_pro_k(rt->scene->cam.horizontal, rt->scene->stereo))\
			, rt->scene->cam.lookat, rt->scene->cam.fov);
	rt->scene->camm[1] = rt_init_camera(vec_sub(rt->scene->cam.lookfrom\
		, vec_pro_k(rt->scene->cam.horizontal, rt->scene->stereo))\
		, rt->scene->cam.lookat, rt->scene->cam.fov);
}

t_vec		rt_stereoscopy(t_thread *t, double col, double row, int select)
{
	t_vec	b_r_col[2];
	t_vec	color;
	t_vec	tab[9];
	t_ray	r;
	double	anti_a;

	anti_a = sqrt(t->rt->scene->max_anti_a);
	init_tab(tab);
	r = rt_get_ray(&t->rt->scene->camm[0]\
		, (double)((col + ((tab[select].x + 0.5) / anti_a)) / IMG_WIDTH)\
		, (double)((row + ((tab[select].y + 0.5) / anti_a)) / IMG_HEIGHT));
	b_r_col[0] = rt_raytracer(t, r, MAX_DEPTH);
	r = rt_get_ray(&t->rt->scene->camm[1]
		, (double)((col + ((tab[select].x + 0.5) / anti_a)) / IMG_WIDTH)
			, (double)((row + ((tab[select].y + 0.5) / anti_a)) / IMG_HEIGHT));
	b_r_col[1] = rt_raytracer(t, r, MAX_DEPTH);
	color.x = b_r_col[0].x;
	color.y = (b_r_col[0].y + b_r_col[1].y) / 2;
	color.z = b_r_col[1].z;
	return (color);
}
