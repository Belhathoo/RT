#include <rt.h>

void		sphere_uv(t_object *o, t_hit *rec)
{
	double	phi;
	double	theta;
	t_vec	p;
    
 	 p = vec_sub(rec->p, o->pos); 
	 p = vec(vec_dot(p, o->vec1), vec_dot(p, o->vec2), vec_dot(p, o->rot));
	phi = atan2(p.z, p.x);
	theta = asin(p.y / o->size);
	rec->u = (phi + M_PI) / (2.0 * M_PI); 
	rec->v = (theta + M_PI / 2.0) / M_PI ;
	return;
}


// int     rt_hit_sphere(t_object *obj, t_ray *ray, t_hit *record)
// {
// 	record->or = vec_sub(ray->origin, obj->pos);// ray origin
// 	record->a = vec_dot(ray->dir, ray->dir);
// 	record->b = 2.0 * vec_dot(record->or, ray->dir); 
// 	record->c = vec_dot(record->or, record->or) - (obj->size * obj->size);
// 	record->delta = record->b * record->b - 4.0 * record->a * record->c;

// 	if (record->delta >= 0.0)
// 	{
// 		record->t0 = (-record->b - sqrt(record->delta)) / (2 * record->a);
// 		record->t1 = (-record->b + sqrt(record->delta)) / (2 * record->a);
// 		record->t = record->t0 < record->t1 ? record->t0 : record->t1;
// 		if (record->t >= 1e-4 && record->t < record->closest)
// 		{
// 			record->p = vec_ray(ray, record->t);
// 			record->n = vec_unit(vec_sub(record->p, obj->pos));
// 			sphere_uv(obj, record);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

int			rt_hit_sphere(t_object *sphere, t_ray *r, t_hit *rec)
{
	rec->or = vec_sub(r->origin, sphere->pos);
	rec->coef[0] = vec_dot(r->dir, r->dir);
	rec->coef[1] = 2 * vec_dot(rec->or, r->dir);
	rec->coef[2] = vec_dot(rec->or, rec->or) - pow(sphere->size, 2);
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta > 0)
	{
		rec->t0 = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
		rec->t1 = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
		(rec->t0 < rec->t1) ? 0 : ft_float_swap(&rec->t0, &rec->t1);
		if (rec->t0 < rec->closest && rec->t0 > MIN)
		{
			rec->t = rec->t0;
			rec->p = vec_ray(r, rec->t);
			rec->n = vec_div_k(vec_sub(rec->p, sphere->pos), sphere->size);
			sphere_uv(sphere, rec);
			if (sphere->is_sliced == 1 && rt_slicing(sphere, r, rec) == 0)
				return (0);
			return (1);
		}
	}
	return (0);
}
