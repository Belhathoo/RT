
#include <rt.h>

 int      cutt_plane(t_hit *rec, t_object *o)
 {
    double largeur = 4.0;
    double longeur = 4.0;

    if ((fabs(vec_dot(rec->p, o->vec1)) > largeur || fabs(vec_dot(rec->p, o->vec2)) > longeur))
        return (0);
    else 
    return (1);
 }

  void			plane_uv(t_hit *rec, t_object *o)
{
    int scale;
  
	rec->u = vec_dot(vec_div_k(vec_sub(rec->p, o->pos), 10.0),
			o->vec2);
	rec->v = vec_dot(vec_div_k(vec_sub(rec->p, o->pos), 10.0),
			o->vec1);
    rec->u = rec->u - floor(rec->u);
	rec->v = rec->v - floor(rec->v);

}

int     rt_hit_plan(t_object *obj, t_ray *ray, t_hit *record)
{
    record->t = ((vec_dot(obj->rot, obj->pos) - vec_dot(obj->rot, ray->origin))
			/ vec_dot(obj->rot, ray->dir));
	if (record->t >= 1e-4 && record->t < record->closest)
    {
        record->p = vec_ray(ray, record->t);
	    record->n = obj->rot;
        // if (cutt_plane(record, obj) == 0)
        //     return (0);
        plane_uv(record, obj);
        return (1);
    }
	return (0);
}