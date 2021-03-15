/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 10:55:26 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/13 16:00:49 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vec		rt_get_rec_col(t_object *o, t_hit *rec, t_rt *rt)
{
	if (o->txt.is_txt == 1)
		return (rt_get_color_from_texture(o, &rec->u, &rec->v));
	else if (o->noi.is_noise == 1)
		return (rt_noise(rt, o, rec));
	else
		return (o->col);
}

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
		rec.col = rt_get_rec_col(o, &rec, th->rt);
		th->rec = rec;
		color = rt_lighting(th, th->rt->scene->light);
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

void		rt_start(t_rt *rt, void *(*rt_runner)(t_thread *t))
{
	pthread_t	thread[NBTHREAD];
	t_thread	div[NBTHREAD];
	int			i;

	i = -1;
	if (rt->scene->stereo)
		rt_init_stereo(rt);
	while (++i < NBTHREAD)
	{
		div[i].rt = rt;
		div[i].i = i;
		pthread_create(&thread[i], NULL, (void*)rt_runner, &div[i]);
	}
	while (--i >= 0)
		pthread_join(thread[i], NULL);
}

void		rt_set_filter(t_rt *rt)
{
	if (rt->filter == SEPIA)
		rt_sepia_filter(rt->data);
	else if (rt->filter == NEGATIVE)
		rt_filter_neg(rt->data);
	else if (rt->filter == GRAY)
		rt_filter_gray(rt->data);
}

int			progress_bar(t_rt *rt)
{
	if (!rt->scene->dyn)
	{
		if (rt->scene->key_mvt == 0)
		{
			rt_progress_run(rt);
			if (rt->scene->progress <= 12\
					&& rt->scene->select <= rt->scene->aa + 1)
			{
				progress_fill(rt);
				rt->scene->progress++;
				if (rt->filter && rt->scene->select == rt->scene->aa)
					rt_set_filter(rt);
				mlx_put_image_to_window(rt->mlx, rt->win, rt->img\
						, FRAME_LFT, FRAME_UP);
			}
		}
	}
	rt_mvt_run(rt);
	return (0);
}
