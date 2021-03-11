/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 10:55:26 by belhatho          #+#    #+#             */
/*   Updated: 2021/02/28 17:03:08 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vec		rt_raytracer(t_thread *th, t_ray r, int depth)
{
	t_vec		color;
	t_object	*o;
	t_hit		rec;

	rec.curr_obj = NULL;
	rec.col = vec3(0.0);
	color = vec3(0.0);
	if (rt_hit(th->rt->scene, &r, &rec, MAX))
	{
		o = rec.curr_obj;
		if (o->txt.is_txt == 1)
			rec.col = rt_get_color_from_texture(o, &rec.u, &rec.v);
		else if (o->noi.is_noise == 1)
			rec.col = rt_noise(o, &rec);
		else
			rec.col = o->col;
		th->rec = rec;
		color = rt_lighting(th, th->RS->light);
		if (depth > 1)
		{
			color = vec_add(color, (o->refl) ? vec_pro_k(rt_raytracer(th,\
			rt_reflection(th->rec, r), depth - 1), o->refl) : vec3(0.0));
			color = vec_add(color, (o->refr) ? (rt_raytracer(th,\
			rt_refraction(th->rec, r, o), depth - 1)) : vec3(0.0));
		}
	}
	rt_adjustment(&color);
	return (color);
}

void		rt_start(t_rt *rt, void* (*rt_runner)(t_thread *t))
{
	pthread_t	thread[NBTHREAD];
	t_thread	div[NBTHREAD];
	int			i;

	i = -1;
	while (++i < NBTHREAD)
	{
		div[i].rt = rt;
		div[i].i = i;
		pthread_create(&thread[i], NULL, (void*)rt_runner, &div[i]);
	}
	while (--i >= 0)
		pthread_join(thread[i], NULL);
}

int		progress_bar(t_rt *rt)
{
	// if ((RS->key_mvt == 0 || RS->key == 1)\
	// 	&& (RS->progress <= 12 && RS->select <= RS->aa + 1))
	// {
	// 	// mlx_destroy_image(rt->mlx, rt->img);
	// 	// rt->img = mlx_new_image(rt->mlx, IMG_WIDTH, IMG_HEIGHT + 8);
	// 	// ft_bzero(rt->data, IMG_WIDTH * IMG_HEIGHT * 4);
	// 	// ft_putstr("--00\n");
	// }
	if (RS->key_mvt == 0)
	{
		RS->key_cam = 0;
		if (RS->progress == 1)
			rt_start(rt, rt_run_12);
		else if (RS->progress == 2)
			rt_start(rt, rt_run_25);
		else if (RS->progress == 3)
			rt_start(rt, rt_run_50);
		else if (RS->progress >= 4 && RS->progress <= 12\
			&& RS->select <= RS->aa + 1)
		{
			rt_start(rt, rt_run);
			RS->select++;
		}
		if (RS->progress <= 12 && RS->select <= RS->aa + 1)
		{
			progress_fill(rt);
			RS->progress++;
			mlx_put_image_to_window(rt->mlx, rt->win, rt->img\
				, FRAME_LFT, FRAME_UP);
			// ft_putendl("aa");
		}
	}
	if (RS->key_mvt == 1 && RS->key == 1)
	{
		rt_start(rt, rt_run_12);
		RS->progress = 0;
		RS->key = 0;
		mlx_put_image_to_window(rt->mlx, rt->win, rt->img, FRAME_LFT, FRAME_UP);
	}
	return (0);
}
