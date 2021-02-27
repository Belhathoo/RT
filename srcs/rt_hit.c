/* ************************************************************************** */

#include <rt.h>

int rt_hit(t_scene *scene, t_ray *r, t_hit *rec, double closest)
{
	t_object	*o;
	int			check_hit;
	t_hit		record;

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
