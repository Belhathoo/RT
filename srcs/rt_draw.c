# include <rt.h>

t_ray		rt_ray(t_vec a, t_vec b)
{
	t_ray	r;

	r.origin = a;
	r.dir = b;
	return (r);
}

static t_ray rt_get_ray(t_camera *p, double u, double v)
{
	return (rt_ray(p->origin, vec_unit(vec_sub(vec_add(p->lower_left_corner,
							vec_add(vec_pro_k(p->horizontal, u),
								vec_pro_k(p->vertical, v))), p->origin))));
}


t_vec rt_raytracer(t_thread *th, t_ray *r, int depth)
{
	t_vec		color;
	t_object	*o;
	int			c;
    int			l = 1;
	
	th->rec.col = vec(0.0, 0.0, 0.0);
	color = vec(0.0, 0.0, 0.0);
	if (rt_hit(th->rt->scene, r, &th->rec))
	{
		o = th->rec.curr_obj;	
		if(o->txt)
		{		// "is_txt = 1 => Damier txt" else "Img txt"
			if (o->txt->is_txt == 1)
				th->rec.col =  rt_txt_damier(&th->rec);
			else
				th->rec.col = rt_get_color_from_texture(o, &th->rec.u, &th->rec.v);
		}
		else
			th->rec.col = th->rec.curr_obj->col;
		rt_lighting(th, th->rt->scene->light);
		color = th->rec.col;

		// t_ray rf;
		// if (depth > 1 && !ft_strcmp(th->rec.curr_obj->name, "PLANE"))
		// {
		// 	rf.dir = ft_reflect(r->dir, th->rec.n);
		// 	rf.origin = vec_add(th->rec.p, vec_pro_k(rf.dir, 0.001));
		// 	color = vec_add(color, vec_pro_k(rt_raytracer(th, &rf, depth -1), 0.7));
		// }
	}
	// color = th->rec.col;
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


int			equal(t_vec vect1, t_vec vect2)
{
	if (vect1.y == vect2.y)
		return (1);
	if (vect1.y == -vect2.y)
		return (2);
	return (0);
}


// void	set_repere(t_vec dir, t_vec *vec1, t_vec *vec2)
// {
// 	t_vec	up;

// 	up = vec(0.0, 1.0, 0.0);

// 	if (equal(up, dir) == 1)
// 	{
// 		*vec1 = vec(1.0, 0.0, 0.0);
// 		*vec2 = vec(0.0, 0.0, 1.0);
// 	}
// 	else
// 	{
// 		if (equal(up, dir) == 2)
// 		{
// 			*vec1 = vec(-1.0, 0.0, 0.0);
// 			*vec2 = vec(0.0, 0.0, 1.0);
// 		}
// 		else
// 		{
// 			*vec1 = vec_cross(up, dir);
// 			*vec2 = vec_cross(*vec1, dir);
// 		}
// 	}
// }


void	rt_get_repere(t_scene *scene)
{
	t_object *o;
	o = scene->object;
	while (o)
  {

	//set_repere(o->rot, &o->vec1, &o->vec2);
	if (o->rot.x == 0.0 && o->rot.y == 0.0)
		o->vec1 = vec(1 / sqrt(2), 1 / sqrt(2), 0);
	else if (o->rot.x == 0.0 && o->rot.z == 0.0)
		o->vec1 = vec(1 / sqrt(2), 0, 1 / sqrt(2));
	else if (o->rot.z == 0.0 && o->rot.y == 0.0)
		o->vec1 = vec(0, 1 / sqrt(2), 1 / sqrt(2));
	else if (o->rot.x == 0.0)
		o->vec1 = vec(1, 0, 0);
	else if (o->rot.y == 0.0)
		o->vec1 = vec(0, 1, 0);
	else if (o->rot.z == 0.0)
		o->vec1 = vec(0, 0, 1);
	 else
		o->vec1 = vec_unit(vec(-(o->rot.y + o->rot.z) / o->rot.x, 1, 1));
		o->vec2 = (vec_cross(o->rot ,o->vec1));
		o = o->next;
  }	
}

void		rt_start(t_rt *rt) 
{
	pthread_t	thread[NBTHREAD];
	t_thread	div[NBTHREAD];
	int i;

	i = -1;
   //rt_get_repere(rt->scene);
   //add_(rt->scene->object);
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