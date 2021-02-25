
# include <rt.h>

void    rt_free_objects(t_object *object)
{
	t_object	*obj;
	t_object	*tmp;

	obj = object;
	while (obj != NULL)
	{
		tmp = obj->next;
		free(obj->name);
    	free(obj->material);
    	free(obj->txt);
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

void    rt_exit(t_rt *rt, char *msg, int err)
{
  /*  certain cases xml free !
  */
  if (err == EXIT_FAILURE)
  {
    ft_putstr("error: ");
    ft_putendl(msg);
    // if (msg)
    //   free(msg);
    rt_free_lights(rt->scene->light);
    rt_free_objects(rt->scene->object);
    free(rt->scene);
    rt = NULL; //unused error fixing
    exit(err);
  }
  exit(err);
}

int			rt_close(t_rt *rt)
{
	mlx_destroy_image(rt->mlx, rt->img);
	mlx_destroy_window(rt->mlx, rt->win);
  rt_exit(rt, ft_strdup("HAPPY CODING"), EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}