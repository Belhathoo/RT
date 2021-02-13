
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

// int     rt_hit_cone(t_object *obj, t_ray *ray, t_hit *record)
// {
//     double aux;
//     t_vec tmp;

//     record->or = vec_sub(ray->origin, obj->pos);
//     aux = vec_dot(ray->dir, vec_unit(obj->rot));
//     record->a = vec_dot(ray->dir, ray->dir) - (1 + pow(tan(obj->size), 2)) * pow(aux, 2);
//     record->b = 2 * (vec_dot(ray->dir, record->or) - (1 + pow(tan(obj->size), 2)) 
//         * aux * vec_dot(record->or, vec_unit(obj->rot)));
//     record->c = vec_dot(record->or, record->or) - (1 + pow(tan(obj->size), 2)) 
//         * pow(vec_dot(record->or, vec_unit(obj->rot)), 2);
//     record->delta = pow(record->b, 2) - 4.0 * record->a * record->c;
//      if(record->delta < 0)
//         return (0);
//     record->t0 = (-record->b - sqrt(record->delta)) / (2 * record->a);
// 	record->t1 = (-record->b + sqrt(record->delta)) / (2 * record->a);
// 	record->t = record->t0 < record->t1 ? record->t0 : record->t1;
//     if (record->t >= 1e-4 && record->t < record->closest)
//     {
//         record->p = vec_ray(ray, record->t);
//         record->n = normale_cone(obj, ray, record);
//         cone_uv(obj, record);
// 		if (obj->is_sliced == 1 && rt_slicing(obj, ray, record) == 0)
// 				return (0);
// 	    return (1);
//     }
// 	return (0);
// }

int			rt_hit_cone(t_object *o, t_ray *r, t_hit *rec)
{
	// o->size *= M_PI / 180 / 2;
	rec->or = vec_sub(r->origin, o->pos);
	rec->coef[0] = vec_dot(r->dir, r->dir) - (1 + pow(tan(o->size), 2))
		* pow(vec_dot(r->dir, o->rot), 2);
	rec->coef[1] = 2 * (vec_dot(r->dir, rec->or) - (1 + pow(tan(o->size), 2))
			* vec_dot(r->dir, o->rot) * vec_dot(rec->or, o->rot));
	rec->coef[2] = vec_dot(rec->or, rec->or) - (1 + pow(tan(o->size), 2))
		* pow(vec_dot(rec->or, o->rot), 2);
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta < 0)
		return (0);
	rec->t0 = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
	rec->t1 = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
	rec->t0 = (rec->t0 > MIN && rec->t0 < rec->t1) ?
					rec->t0 : rec->t1;
	if (rec->t0 < rec->closest && rec->t0 > MIN)
	{
		rec->t = rec->t0;
		rec->p = vec_ray(r, rec->t);
		rec->tmp = vec_pro_k(o->rot, (vec_dot(r->dir, o->rot) * rec->t
					+ vec_dot(rec->or, o->rot)));
		rec->tmp = vec_pro_k(rec->tmp, (1 + pow(tan(o->size), 2)));
        rec->n = normale_cone(o, r, rec);
		cone_uv(o, rec);
		if (o->is_sliced == 1 && rt_slicing(o, r, rec) == 0)
				return (0);
        return (1);
	}
	return (0);
}
