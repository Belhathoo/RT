/* ************************************************************************** */

#include <rt.h>


int			rt_slicing(t_object *o, t_ray *r, t_hit *rec)
{
	/*
		slicing for (sphere / cylinder / )
	*/

	t_vec     ax;
	t_vec     my;
  t_object  plan;
	
  ax = vec_unit(o->sl_vec);
  my = vec_unit(vec_sub(rec->p, vec_add(o->pos, o->sl_pnt)));
	if (vec_dot(my, ax) <= 0)
	{
		plan.pos = o->pos;
		plan.rot = vec_pro_k(ax, -1);
		rec->t = rec->t1;
		rec->p = vec_ray(r, rec->t);
		my = vec_unit(vec_sub(rec->p, o->pos));
		if (vec_dot(my, ax) <= 0)
			return(0);
		return(rt_hit_plan(&plan, r, rec));
	}
	return (1);
}

int rt_hit(t_scene *scene, t_ray *r, t_hit *record)
{
  t_object  *obj;
  int      check_hit;

  check_hit = 0;
  record->closest = MAX;
  obj = scene->object;
  while (obj)
  {
    if (obj->hit(obj, r, record))
    {
      record->closest = record->t;
      record->curr_obj = obj;
      record->ray = r;
      check_hit = 1;
    }
    obj = obj->next;
  }
  return (check_hit);
}