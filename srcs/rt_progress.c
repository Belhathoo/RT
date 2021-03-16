/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_progress.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:59:11 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/16 16:03:36 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		rt_progress_run(t_rt *rt)
{
	rt->scene->key_cam = 0;
	if (rt->scene->progress == 1)
		rt_start(rt, rt_run_12);
	else if (rt->scene->progress == 2)
		rt_start(rt, rt_run_25);
	else if (rt->scene->progress == 3)
		rt_start(rt, rt_run_50);
	else if (rt->scene->progress >= 4 && rt->scene->progress <= 12\
			&& rt->scene->select <= rt->scene->aa + 1)
	{
		rt_start(rt, rt_run);
		rt->scene->select++;
	}
}

void		rt_dynamic_milky(t_object *o)
{
	while (o)
	{
		if (ft_strcmp(o->name, "plan"))
			o->pos = rotation(o->pos, vec(0.0, 1.0, 0.0));
		o = o->next;
	}
}

void		rt_dynamic_holo(t_scene *scene)
{
	scene->cam.lookfrom = rotation(scene->cam.lookfrom\
					, vec(0.0, 2.0, 0.0));
	scene->cam = rt_init_camera(scene->cam.lookfrom\
					, scene->cam.lookat, scene->cam.fov);
}

void		rt_mvt_run(t_rt *rt)
{
	t_object	*o;

	if (rt->scene->dyn)
	{
		rt_start(rt, rt_run_50);
		rt->scene->key = 1;
		o = rt->scene->object;
		if (rt->scene->dyn == 1)
			rt_dynamic_milky(o);
		else
			rt_dynamic_holo(rt->scene);
		mlx_put_image_to_window(rt->mlx, rt->win, rt->img, FRAME_LFT, FRAME_UP);
	}
	else if (rt->scene->key_mvt == 1 && rt->scene->key == 1)
	{
		rt_start(rt, rt_run_50);
		rt->scene->progress = 0;
		rt->scene->key = 0;
		mlx_put_image_to_window(rt->mlx, rt->win, rt->img, FRAME_LFT, FRAME_UP);
	}
}
