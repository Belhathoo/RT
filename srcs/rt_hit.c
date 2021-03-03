/* ************************************************************************** */

#include <rt.h>

void	rt_init_negative(t_hit *rec)
{
	rec->negative[0] = 0;
	rec->negative[1] = 0;
	rec->negative_normal = (t_vec){0, 0, 0};
}

int rt_hit(t_scene *scene, t_ray *r, t_hit *rec, double closest)
{
	t_object	*o;
	int			check_hit;
	t_hit		record;

	//negatives clean code
	if (scene->is_neg == 0)
		rt_init_negative(&record);
	else
		scene->n_obj.hit(&scene->n_obj, r, &record);
	check_hit = 0;
	o = scene->object;
	record.closest = closest;
	record.curr_obj = NULL;
	while (o)
	{
		if (o->hit(o, r, &record))
		{
			check_hit = 1;
			record.closest = record.t;
			record.curr_obj = o;
			record.ray = r;
			*rec = record;
		}
		o = o->next;
	}
	return (check_hit);
}
