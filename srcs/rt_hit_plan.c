
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

int     rt_hit_plan(t_object *o, t_ray *r, t_hit *rec)
{
    rec->t = ((vec_dot(o->rot, o->pos) - vec_dot(o->rot, r->origin))
			/ vec_dot(o->rot, r->dir));
	if (rec->t >= rec->closest || rec->t <= MIN)
		return (0);
	rec->p = vec_ray(r, rec->t);
    if (cutt_plane(rec, o) == 0)
           return (0);
	rec->n = o->rot;
	plane_uv(rec, o);
    return (1);
}

// int         rt_hit_caree(t_object *o, t_ray *ray, t_hit *rec)
// { 
//     rec->t = ((vec_dot(o->rot, o->pos) - vec_dot(o->rot, ray->origin))
// 			/ vec_dot(o->rot, ray->dir));
//    if (rec->t >= 1e-4 && rec->t < rec->closest)
//     {
//         rec->p = vec_ray(ray, rec->t);
//         if (cutt_plane(rec, o) == 0)
//            return (0);
// 	    rec->n = o->rot;
//         plane_uv(rec, o);
//         return (1);
//     }
// 	return (0);
// }