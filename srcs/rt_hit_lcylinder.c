
#include <rt.h>

int     rt_lcylinder_params(t_object *obj, t_ray *ray, t_hit *rec)
{
	double	m;
    double min_sol;

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
		min_sol = rec->t0;
		if (min_sol < rec->closest && min_sol >= MIN)
		{
			rec->t = min_sol;
            return (1);
		}
	}
	return (0);
}

// int     rt_hit_lcylinder(t_object *obj, t_ray *ray, t_hit *rec)
// {
//     if (rt_lcylinder_params(obj, ray, rec))
//     {
//             rec->p = vec_ray(ray, rec->t);
// 			rec->n = normale_cylinder(obj, ray, rec);
// 			rec->n = (rec->t0 > rec->t1) ? vec_pro_k(rec->n, -1) : rec->n;
// 			cylinder_uv(obj, rec);
// 			return (1);
//     }
// }
int     rt_hit_lcylinder(t_object *obj, t_ray *ray, t_hit *rec)
{
	//limited cylinder
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