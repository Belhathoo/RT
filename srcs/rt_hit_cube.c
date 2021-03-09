
#include <rt.h>

int				rt_hit_cube(t_object *obj, t_ray *r,  t_hit *rec)
{
	t_object	*o;
	double		closest;
	int			check_hit;
	t_hit		record;

	check_hit = 0;
	o = obj->compos;
	record.closest = rec->closest;
	record.curr_obj = NULL;
	while (o)
	{
		if (o->hit(o, r, &record))
		{
			check_hit = 1;
			record.closest = record.t;
	
			rec->t = record.t;
			rec->p = record.p;
			rec->n = record.n;
			rec->u = record.u;
			rec->v = record.v;
			rec->closest = rec->t;
			RCR = o;
			rec->ray = r;
			// record.ray = r;
			// *rec = record;
		}
		o = o->compos;	
	}
	return (check_hit);
}