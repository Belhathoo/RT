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

t_vec		normale_cylinder(t_object *o, t_ray *r, t_hit *rec)
{
	t_vec normale;

	normale = vec_unit(vec_sub(vec_sub(rec->p, o->pos),
			 vec_pro_k(vec_unit(o->rot), vec_dot(r->dir, 
			 vec_unit(o->rot))* rec->t + vec_dot(rec->or, 
			 vec_unit(o->rot)))));
	// rec->n = normale;
	return (normale);
} 

int     rt_hit_cylinder(t_object *obj, t_ray *ray, t_hit *rec)
{
    rec->or = vec_sub(ray->origin, obj->pos);
	rec->a = vec_dot(ray->dir, ray->dir) - pow(vec_dot(ray->dir, vec_unit(obj->rot)), 2);
	rec->b = 2 * (vec_dot(ray->dir, rec->or) - (vec_dot(ray->dir, vec_unit(obj->rot))
				* vec_dot(rec->or, vec_unit(obj->rot))));
	rec->c = vec_dot(rec->or, rec->or) - pow(vec_dot(rec->or, vec_unit(obj->rot)), 2)
		- obj->size * obj->size;
	rec->delta = rec->b * rec->b - 4.0 * rec->a * rec->c;
	if (rec->delta >= 0)
  {
		rec->t0 = (-rec->b - sqrt(rec->delta)) / (2 * rec->a);
		rec->t1 = (-rec->b + sqrt(rec->delta)) / (2 * rec->a);
		rec->t = (rec->t0 < rec->t1) ? rec->t0 : rec->t1;
    if (rec->t < rec->closest && rec->t >= 1e-4)
    {
			rec->p = vec_ray(ray, rec->t);
			rec->n = normale_cylinder(obj, ray, rec);
			cylinder_uv(obj, rec);
			return (1);
	}
 }
	return (0);
}


int     rt_hit_l_cylinder(t_object *obj, t_ray *ray, t_hit *rec)
{//limited cylinder
	double	m;

    rec->or = vec_sub(ray->origin, obj->pos);
	rec->a = vec_dot(ray->dir, ray->dir) - pow(vec_dot(ray->dir, vec_unit(obj->rot)), 2);
	rec->b = 2 * (vec_dot(ray->dir, rec->or) - (vec_dot(ray->dir, vec_unit(obj->rot))
				* vec_dot(rec->or, vec_unit(obj->rot))));
	rec->c = vec_dot(rec->or, rec->or) - pow(vec_dot(rec->or, vec_unit(obj->rot)), 2)
		- obj->size * obj->size;
	rec->delta = rec->b * rec->b - 4.0 * rec->a * rec->c;
	if (rec->delta >= 0)
	{
		rec->t0 = (-rec->b - sqrt(rec->delta)) / (2 * rec->a);
		rec->t1 = (-rec->b + sqrt(rec->delta)) / (2 * rec->a);
		(rec->t0 < rec->t1) ? 0 : ft_float_swap(&rec->t0, &rec->t1);
		m = vec_dot(ray->dir, obj->rot) * rec->t0 + vec_dot(rec->or, obj->rot);
		if (m <= -obj->height/2 || m >= obj->height/2)
		{
			m = vec_dot(ray->dir, obj->rot) * rec->t1 + vec_dot(rec->or, obj->rot);
			if (m <= -obj->height/2 || m >= obj->height/2)
				return (0);
			ft_float_swap(&rec->t0, &rec->t1);
		}
		rec->t = rec->t0;
		if (rec->t < rec->closest && rec->t >= EPS)
		{
			rec->p = vec_ray(ray, rec->t);
			rec->n = normale_cylinder(obj, ray, rec);
			rec->n = (rec->t0 > rec->t1) ? vec_pro_k(rec->n, -1) : rec->n;
			cylinder_uv(obj, rec);
			return (1);
		}
	}
	return (0);
}
