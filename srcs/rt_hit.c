/* ************************************************************************** */

#include <rt.h>

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