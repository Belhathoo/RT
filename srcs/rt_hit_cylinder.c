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
	rec->u = rec->u - floor(rec->u);
    rec->v = rec->v - floor(rec->v);
}

t_vec		normale_cylinder(t_object *o, t_ray *r, t_hit *rec, t_hit *rec1)
{
	t_vec normale;

	rec->t = rec1->t;
	rec->p = rec1->p;
	rec->ray = r;
	normale = vec_unit(vec_sub(vec_sub(rec->p, o->pos),
			 vec_pro_k(vec_unit(o->rot), vec_dot(r->dir, 
			 vec_unit(o->rot))* rec->t + vec_dot(rec1->or, 
			 vec_unit(o->rot)))));
	rec->n = normale;
	return (normale);
} 

int     rt_hit_cylinder(t_object *obj, t_ray *ray, t_hit *record)
{
	t_hit	rec1;

    rec1.or = vec_sub(ray->origin, obj->pos);
	rec1.a = vec_dot(ray->dir, ray->dir) - pow(vec_dot(ray->dir, vec_unit(obj->rot)), 2);
	rec1.b = 2 * (vec_dot(ray->dir, rec1.or) - (vec_dot(ray->dir, vec_unit(obj->rot))
				* vec_dot(rec1.or, vec_unit(obj->rot))));
	rec1.c = vec_dot(rec1.or, rec1.or) - pow(vec_dot(rec1.or, vec_unit(obj->rot)), 2)
		- obj->size * obj->size;
	rec1.delta = rec1.b * rec1.b - 4.0 * rec1.a * rec1.c;
	if (rec1.delta >= 0)
  {
		rec1.t0 = (-rec1.b - sqrt(rec1.delta)) / (2 * rec1.a);
		rec1.t1 = (-rec1.b + sqrt(rec1.delta)) / (2 * rec1.a);
		rec1.t = (rec1.t0 < rec1.t1) ? rec1.t0 : rec1.t1;
    if (rec1.t < record->closest && rec1.t >= 1e-4)
    {
			rec1.p = vec_ray(ray, rec1.t);
			normale_cylinder(obj, ray, record, &rec1);
			cylinder_uv(obj, record);
			return (1);
	}
 }
	return (0);
}


int     rt_hit_l_cylinder(t_object *obj, t_ray *ray, t_hit *record)
{//limited cylinder
	t_hit	rec1;
	double	m;

    rec1.or = vec_sub(ray->origin, obj->pos);
	rec1.a = vec_dot(ray->dir, ray->dir) - pow(vec_dot(ray->dir, vec_unit(obj->rot)), 2);
	rec1.b = 2 * (vec_dot(ray->dir, rec1.or) - (vec_dot(ray->dir, vec_unit(obj->rot))
				* vec_dot(rec1.or, vec_unit(obj->rot))));
	rec1.c = vec_dot(rec1.or, rec1.or) - pow(vec_dot(rec1.or, vec_unit(obj->rot)), 2)
		- obj->size * obj->size;
	rec1.delta = rec1.b * rec1.b - 4.0 * rec1.a * rec1.c;
	if (rec1.delta >= 0)
	{
		rec1.t0 = (-rec1.b - sqrt(rec1.delta)) / (2 * rec1.a);
		rec1.t1 = (-rec1.b + sqrt(rec1.delta)) / (2 * rec1.a);
		(rec1.t0 < rec1.t1) ? 0 : ft_float_swap(&rec1.t0, &rec1.t1);
		m = vec_dot(ray->dir, obj->rot) * rec1.t0 + vec_dot(rec1.or, obj->rot);
		if (m <= -obj->height/2 || m >= obj->height/2)
		{
			m = vec_dot(ray->dir, obj->rot) * rec1.t1 + vec_dot(rec1.or, obj->rot);
			if (m <= -obj->height/2 || m >= obj->height/2)
				return (0);
			ft_float_swap(&rec1.t0, &rec1.t1);
		}
		rec1.t = rec1.t0;
		if (rec1.t < record->closest && rec1.t >= 1e-4)
		{
			rec1.p = vec_ray(ray, rec1.t);
			normale_cylinder(obj, ray, record, &rec1);
			record->n = (rec1.t0 > rec1.t1) ? vec_pro_k(record->n, -1) : record->n;
			cylinder_uv(obj, record);
			return (1);
		}
	}
	return (0);
}
