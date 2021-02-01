#include <rt.h>


void	cylinder_uv(t_object *o, t_hit *rec)
{
	int scale;
	t_vec d;
    
	scale = 1;
	d = vec_pro_k(vec_sub(rec->p, o->pos), 1);
	d = vec_div_k(vec(vec_dot(d, o->vec1), vec_dot(d, o->rot), vec_dot(d, o->vec2)), scale);
	rec->u = (atan2(d.x, d.z) + M_PI / (2.0 * M_PI));
	rec->v = d.y / o->size;
	//rec->u = rec->u - floor(rec->u);
    //rec->v = rec->v - floor(rec->v);
}

t_vec		normale_cylinder(t_object *o, t_ray *r, t_hit *rec)
{
	t_vec normale;

	normale = vec_unit(vec_sub(vec_sub(rec->p, o->pos),
			 vec_pro_k(vec_unit(o->rot), vec_dot(r->dir, 
			 vec_unit(o->rot))* rec->t + vec_dot(rec->or, 
			 vec_unit(o->rot)))));
	return (normale);
} 

int     rt_hit_cylinder(t_object *obj, t_ray *ray, t_hit *record)
{

    record->or = vec_sub(ray->origin, obj->pos);
	record->a = vec_dot(ray->dir, ray->dir) - pow(vec_dot(ray->dir, vec_unit(obj->rot)), 2);
	record->b = 2 * (vec_dot(ray->dir, record->or) - (vec_dot(ray->dir, vec_unit(obj->rot))
				* vec_dot(record->or, vec_unit(obj->rot))));
	record->c = vec_dot(record->or, record->or) - pow(vec_dot(record->or, vec_unit(obj->rot)), 2)
		- obj->size * obj->size;
	record->delta = record->b * record->b - 4.0 * record->a * record->c;
	if (record->delta >= 0)
  {
		record->t0 = (-record->b - sqrt(record->delta)) / (2 * record->a);
		record->t1 = (-record->b + sqrt(record->delta)) / (2 * record->a);
		record->t = (record->t0 < record->t1) ? record->t0 : record->t1;
    if (record->t < record->closest && record->t >= 1e-4)
    {
			record->p = vec_ray(ray, record->t);
			record->n = normale_cylinder(obj, ray, record);
			cylinder_uv(obj, record);
			return (1);
	}
 }
	return (0);
}