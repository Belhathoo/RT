
# include <rt.h>

void		rt_perror(void)
{
	perror("error: ");
	exit(EXIT_FAILURE);
}

void    rt_exit(t_rt *rt, char *msg, int err)
{
  if (err == EXIT_FAILURE)
  {
    ft_putstr("error: ");
    ft_putendl(msg);
    // if (msg)
    //   free(msg);
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