/* ************************************************************************** */

#include <rt.h>

int				ft_shading(t_thread *th, t_vec lo)
{
	t_ray		sh_r;
	t_hit	    rec;
	t_object	*o;

	o = th->rt->scene->object;
	sh_r = rt_ray(vec_add(th->rec.p, vec_pro_k(lo, 0.001)), lo);
	rec.closest = vec_length(sh_r.dir);
	sh_r.dir = vec_unit(sh_r.dir);
	while (o != NULL)
	{
		if (o != th->rec.curr_obj)
			if (rt_hit(th->rt->scene, &sh_r, &rec))
				return (1);
		o = o->next;
	}
	return (0);
}

void			ft_ambient(t_light *l, t_thread *th, t_vec *col)
{
	t_object	*o;
	double		ia;
    
	o = th->rec.curr_obj;
	ia = o->ka * th->rt->scene->ambient;
	if (!l)
		*col = vec_pro_k(*col, o->ka);
	else
		*col = vec_pro_k(vec_prod(th->rt->scene->light->col, *col), ia);
}