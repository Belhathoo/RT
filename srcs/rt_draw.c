# include <rt.h>

t_vec rt_raytracer(t_thread *th, t_ray *r, int depth)
{
	t_vec		color;
	t_object	*o;

	th->rec.col = vec(0.0, 0.0, 0.0);
	color = vec(0.0, 0.0, 0.0);
	if (rt_hit(th->rt->scene, r, &th->rec))
	{
		o = th->rec.curr_obj;	
		if (o->txt)
			th->rec.col = rt_get_color_from_texture(o, &th->rec.u, &th->rec.v);
		else if (o->noi.is_noise == 1)
			th->rec.col =  rt_noise(o, th->rec);
		else
			th->rec.col = o->col;
		
		rt_lighting(th, th->rt->scene->light);
		rt_check_l_ref(th, r, o, depth);
		color = th->rec.col;
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
	anti_a = t->rt->scene->anti_aliasing;
	ss[0] = -1;

	while ( ++ss[0] < anti_a)
	{
		ss[1] = -1;
		while (++ss[1] < anti_a)
		{
			r = rt_get_ray(&t->rt->scene->cam, 
					(double)((col + ((ss[0] + 0.5)/ anti_a)) / IMG_WIDTH),
					(double)((row + ((ss[1] + 0.5) / anti_a)) / IMG_HEIGHT));
			color = vec_add(color, rt_raytracer(t, &r, 50));
		}
	}
	return (vec_div_k(color, anti_a * anti_a));
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

void		rt_start(t_rt *rt) 
{
	pthread_t	thread[NBTHREAD];
	t_thread	div[NBTHREAD];
	int i;

	i = -1;
	while (++i < NBTHREAD)
	{
		div[i].rt = rt;
		div[i].i = i;
		pthread_create(&thread[i], NULL, (void*)rt_run, &div[i]);
	}
	while (--i >= 0)
		pthread_join(thread[i], NULL);
}

int			rt_draw(t_rt *rt)
{
	ft_bzero(rt->data, IMG_WIDTH * IMG_HEIGHT * 4);
	rt_start(rt);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 40, 180);
	return (EXIT_SUCCESS);
}
