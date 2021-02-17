#include <rt.h>

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

int     rt_hit_sphere(t_object *obj, t_ray *ray, t_hit *rec)
{
	rec->or = vec_sub(ray->origin, obj->pos);// ray origin
	rec->a = vec_dot(ray->dir, ray->dir);
	rec->b = 2.0 * vec_dot(rec->or, ray->dir); 
	rec->c = vec_dot(rec->or, rec->or) - (obj->size * obj->size);
	rec->delta = rec->b * rec->b - 4.0 * rec->a * rec->c;

	if (rec->delta >= 0.0)
	{
		rec->t0 = (-rec->b - sqrt(rec->delta)) / (2 * rec->a);
		rec->t1 = (-rec->b + sqrt(rec->delta)) / (2 * rec->a);
		rec->t = rec->t0 < rec->t1 ? rec->t0 : rec->t1;
		if (rec->t >= EPS && rec->t < rec->closest)
		{
			rec->p = vec_ray(ray, rec->t);
			rec->n = vec_unit(vec_sub(rec->p, obj->pos));
			sphere_uv(obj, rec);
			return (1);
		}
	}
	return (0);
}

