
# include <rt.h>

void    rt_free_objects(t_object *object)
{
	t_object	*obj;
	t_object	*tmp;
	t_object	*tmp1;
	t_object	*o;

	obj = object;
	while (obj != NULL)
	{
		o = obj->compos;
		while (o)
		{
			tmp1 = o->compos;
			free(o);
			o = tmp1;				
		}
		tmp = obj->next;
		free(obj->name);
		free(obj->material);
		free(obj);
		obj = tmp;
	}
}

void    rt_free_lights(t_light *light)
{
	t_light		*l;
	t_light		*tmp;

	l = light;
	while (l != NULL)
	{
		tmp = l->next;
		free(l);
		l = tmp;
	}
}

void		rt_perror(void)
{
	perror("error: ");
	//exit with rt_exit
	exit(EXIT_FAILURE);
}

void    rt_exit(t_rt *rt, char *m,  int err)
{
	/*  certain cases xml free !
	*/
	if (err == EXIT_FAILURE)
	{
		ft_putstr("error: ");
		ft_putstr(m);
		// ft_putendl(m1);
		// if (msg)
		//   free(msg);
		rt = NULL; //unused error fixing
		exit(err);
	}
		rt_free_lights(RS->light);
		rt_free_objects(RS->object);
		free(rt->bt);
		free(rt->scene);
	exit(err);
}

int			rt_close(t_rt *rt)
{
	mlx_destroy_image(rt->mlx, rt->img);
	mlx_destroy_window(rt->mlx, rt->win);
	rt_exit(rt, ft_strdup("HAPPY CODING"), EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
