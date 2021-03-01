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

# include <rt.h>

t_vec rt_raytracer(t_thread *th, t_ray r, int depth)
{
	t_vec		color;
	t_object	*o;
	t_hit rec;

	rec.curr_obj = NULL;
	rec.col = vec3(0.0);
	color = vec3(0.0);
	if (rt_hit(th->rt->scene, &r, &rec, MAX))
	{
		o = rec.curr_obj;	
		if (o->txt)
			rec.col = rt_get_color_from_texture(o, &rec.u, &rec.v);
		else if (o->noi.is_noise == 1)
			rec.col =  rt_noise(o, &rec);
		else
			rec.col = o->col;
		th->rec = rec;
		color = rt_lighting(th, th->rt->scene->light);
		if (depth > 1)
		{
			color = vec_add(color, (o->refl) ?  vec_pro_k(rt_raytracer(th,\
			rt_reflection(th->rec, r, o), depth - 1), o->refl) : vec3(0.0));	
			color = vec_add(color, (o->refr) ?  (rt_raytracer(th,\
			rt_refraction(th->rec, r, o), depth - 1)) : vec3(0.0));
		}
	}
	rt_adjustment(&color);
	return (color);
}

t_vec rt_anti_aliasing(t_thread *t, int col, int row)
{
	t_ray	r;
	t_vec	color;
	int		ss[2];
	int		anti_a;

	color = vec(0, 0, 0);
	color = anti_aa(t, (double)col, (double)row, t->rt->scene->select); //
	color = vec_div_k(color, t->rt->scene->select + 1); //
	return (color);
}

void		*rt_run(t_thread *t)
{
	t_vec   c;
	int			color;
	int			col;
	int			row;

	row = IMG_HEIGHT + 1;
	while (--row >= 0)
	{
		col = (int)(t->i * IMG_WIDTH / NBTHREAD) - 1;
		while (++col < (int)((t->i + 1) * IMG_WIDTH / NBTHREAD))
		{
			c = rt_anti_aliasing(t, col, row);			
			color = rt_rgb_to_int(c);
			rt_mlx_putpixel(t->rt, col, IMG_HEIGHT - row, color);
		}
	}
	pthread_exit(NULL);
}

void		rt_start(t_rt *rt, void* (*rt_runner)(t_thread *t)) 
{
	pthread_t	thread[NBTHREAD];
	t_thread	div[NBTHREAD];
	int i;

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


void	progress_fill(t_rt *rt)
{
	int i;
	int j;

	(rt->scene->select == rt->scene->aa) ? (rt->scene->progress = 12) : 0;
	i = -1;
	while (++i < ((double)IMG_WIDTH / (double)12) * (double)(rt->scene->progress))
	{
		j = -1;
		while (++j < 8)
			rt_mlx_putpixel(rt, i, IMG_HEIGHT - 4 + j, 0xFF0000);
	}
}

int		progress_bar(t_rt *rt)
{
	if (rt->scene->key == 1 || rt->scene->key2 == 1)
	{
		mlx_destroy_image(rt->mlx, rt->img);
		rt->img = mlx_new_image(rt->mlx, IMG_WIDTH, IMG_HEIGHT + 8);
		ft_bzero(rt->data, IMG_WIDTH * IMG_HEIGHT * 4);
	}
	if (rt->scene->key == 0)
	{
		if (rt->scene->progress == 1)
			rt_start(rt, rt_run_12);
		else if (rt->scene->progress == 2)
			rt_start(rt, rt_run_25);
		else if (rt->scene->progress == 3)
			rt_start(rt, rt_run_50);
		else if (rt->scene->progress >= 4 && rt->scene->progress <= 12 && rt->scene->select <= rt->scene->aa + 1)
		{
			rt_start(rt, rt_run);
			rt->scene->select++;
		}
		if (rt->scene->progress <= 12 && rt->scene->select <= rt->scene->aa + 1)
		{
			progress_fill(rt);
			rt->scene->progress++;
			mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 40, 180);
		}
	}
	else if (rt->scene->key2 == 1)
	{
		rt_start(rt, rt_run_25);
		rt->scene->progress = 0;
		rt->scene->key2 = 0;
		mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 40, 180);
		//ft_putstr("pp");
	}
	return 0;
}
