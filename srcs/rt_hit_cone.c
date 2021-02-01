
#include<rt.h>

void    cone_uv(t_object *o, t_hit *rec)
{
    t_vec d;
    int scale;

    scale = 3;
	d = vec_pro_k(vec_sub(rec->p, o->pos), scale);
	d = vec(vec_dot(d, o->vec1), vec_dot(d, o->rot), vec_dot(d, o->vec2));
	rec->u = (atan2(d.x, d.z) + M_PI / (2.0 * M_PI));
	rec->v = d.y / o->size;
    rec->u = rec->u - floor(rec->u);
    rec->v = rec->v - floor(rec->v);
}

t_vec   normale_cone(t_object *obj, t_ray *ray, t_hit *record)
{
    t_vec normale;

    normale = vec_pro_k(obj->rot, (vec_dot(ray->dir, vec_unit(obj->rot))
     * record->t+ vec_dot(record->or, vec_unit(obj->rot))));
	normale = vec_pro_k(normale, (1 + pow(tan(obj->size), 2)));
       
   return (normale);
}

int     rt_hit_cone(t_object *obj, t_ray *ray, t_hit *record)
{
    double aux;
    t_vec tmp;

    record->or = vec_sub(ray->origin, obj->pos);
    aux = vec_dot(ray->dir, vec_unit(obj->rot));
    record->a = vec_dot(ray->dir, ray->dir) - (1 + pow(tan(obj->size), 2)) * pow(aux, 2);
    record->b = 2 * (vec_dot(ray->dir, record->or) - (1 + pow(tan(obj->size), 2)) 
        * aux * vec_dot(record->or, vec_unit(obj->rot)));
    record->c = vec_dot(record->or, record->or) - (1 + pow(tan(obj->size), 2)) 
        * pow(vec_dot(record->or, vec_unit(obj->rot)), 2);
    record->delta = pow(record->b, 2) - 4.0 * record->a * record->c;
     if(record->delta < 0)
        return (0);
    record->t0 = (-record->b - sqrt(record->delta)) / (2 * record->a);
	record->t1 = (-record->b + sqrt(record->delta)) / (2 * record->a);
	record->t = record->t0 < record->t1 ? record->t0 : record->t1;
    if (record->t >= 1e-4 && record->t < record->closest)
    {
        record->p = vec_ray(ray, record->t);
        record->n = normale_cone(obj, ray, record);
        cone_uv(obj, record);
        return (1);

    }
    return (0);
}