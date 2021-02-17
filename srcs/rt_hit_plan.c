
#include <rt.h>


//add  L l parameters cutt if cube l= L= size
 int      cutt_plane(t_hit *rec, t_object *o)
 {
    double largeur;
    double longeur;
    t_vec   pnt;

    pnt = vec_sub(rec->p, o->pos);
    largeur = o->width;
    longeur = o->height;

    if (!o->name || ft_strcmp(o->name, "rectangle"))
    {
        printf("3iw care!");
        largeur = o->size;
        longeur = largeur;
    }
    if ((fabs(vec_dot(pnt, o->vec1)) > largeur 
            || fabs(vec_dot(pnt, o->vec2)) > longeur))
        return (0);
    else 
        return (1);
 }


  void			plane_uv(t_hit *rec, t_object *o)
{
    int scale;
  
	rec->u = vec_dot(vec_div_k(vec_sub(rec->p, o->pos), 10.0),
			o->vec2);//texture !!!!!!!!!
	rec->v = vec_dot(vec_div_k(vec_sub(rec->p, o->pos), 10.0),
			o->vec1);
    rec->u = rec->u - floor(rec->u);
	rec->v = rec->v - floor(rec->v);

}

int     rt_hit_plan(t_object *o, t_ray *r, t_hit *rec)
{
    double  t;

    t = ((vec_dot(o->rot, o->pos) - vec_dot(o->rot, r->origin))
			/ vec_dot(o->rot, r->dir));
	if (t >= rec->closest || t <= MIN)
		return (0);
    rec->t = t;
	rec->p = vec_ray(r, rec->t);
	rec->n = o->rot;
	plane_uv(rec, o);
    return (1);
}

// int     rt_hit_plan_cube(t_object *o, t_ray *r, t_hit *rec)
// {
//     rec->t = ((vec_dot(o->rot, o->pos) - vec_dot(o->rot, r->origin))
// 			/ vec_dot(o->rot, r->dir));
// 	if (rec->t >= rec->closest || rec->t <= MIN)
// 		return (0);
// 	rec->p = vec_ray(r, rec->t);
// 	rec->n = o->rot;
// 	plane_uv(rec, o);
//     if (cutt_plane(rec, o) == 0)
//            return (0);
//     return (1);
// }

int         rt_hit_care(t_object *o, t_ray *ray, t_hit *rec)
{
    double  t;
    t_hit   rec1;

    rec1.t = ((vec_dot(o->rot, o->pos) - vec_dot(o->rot, ray->origin))
			/ vec_dot(o->rot, ray->dir));
   if (rec1.t >= 1e-4 && rec1.t < rec->closest)
    {
        rec1.p = vec_ray(ray, rec1.t);
   		rec1.n = vec_dot(ray->dir, o->rot) < 0? vec_pro_k(o->rot, -1) : o->rot;
        plane_uv(&rec1, o);
        if (cutt_plane(&rec1, o) == 0)
           return (0);
        rec->t = rec1.t;
        rec->p = rec1.p;
        rec->ray = ray;
        return (1);
    }
	return (0);
}