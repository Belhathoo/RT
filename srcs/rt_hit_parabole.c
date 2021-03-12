

#include <rt.h>

t_vec		rt_parabol_normal(t_ray *ray, t_hit *rec, t_object *obj)
{
	t_vec normal;

	
	
   normal = vec_sub(vec_sub(rec->p, obj->pos),
		vec_pro_k(obj->rot, vec_dot(vec_sub(rec->p,
		obj->pos), obj->rot) + obj->radius));


	return (vec_unit(normal));

}

 static int				rt_check_parab(double c[3], t_ray *ray, t_hit *rec)
{
	double	s[2];
	int		i;
	int		num;
    double  min_sol;

	rec->t = rec->closest;
	i = -1;
	if ((num = rt_solve_quadric(c, s)))
	{
		while (++i < num)
		{
			if (s[i] >= MIN && s[i] < rec->t)
				min_sol = s[i];
		}
		if (min_sol >= MIN && min_sol < rec->closest)
		{
		    rec->t = min_sol;
			return (1);
		}
	}
	return (0);
}

/*static int     rt_init_params(t_object *obj, t_ray *ray, t_hit *record)
{
    t_coef coe;
    double c[3];

    record->or = vec_sub(ray->origin, obj->pos);
    coe.m = 2 * pow(obj->size, 2) * record->or.x * ray->dir.x;
    coe.n = 2 * pow(obj->r, 2) * record->or.y * ray->dir.y;
    coe.o = - pow(obj->size, 2) * pow(obj->r, 2) * ray->dir.z;
    coe.p = - pow(obj->size, 2) * pow(obj->r, 2) * record->or.z;

    c[0] = pow(obj->size, 2) * pow(ray->dir.x, 2) + \
           pow(obj->r, 2) * pow(ray->dir.y, 2);
    c[1] = coe.m + coe.n + coe.o;
    c[2] = pow(obj->size, 2) * pow(record->or.x, 2) + \
           pow(obj->r, 2) * pow(record->or.y, 2) + coe.p;
	
    return (rt_check_parab(c, ray, record));         
}*/



/*static int     rt_init_params(t_object *obj, t_ray *ray, t_hit *record)
{
	double c[3];
	double	xv;
	double	dv;
	t_vec	x;

	int		ret;

	
	x = ray->origin;
	xv = vec_dot(x, obj->rot);
	dv = vec_dot(ray->dir, obj->rot);
	c[2] = vec_dot(ray->dir, ray->dir) - dv * dv;
	c[1] = 2 * (vec_dot(ray->dir, x) - dv * (xv + 2 * obj->scale));
	c[0] = vec_dot(x, x) - xv * (xv + 4 * obj->scale);

	return (rt_check_parab(c, ray, record));    
}*/

double     rt_init_params(t_object *obj, t_ray *ray, t_hit *record)
{
	double c[3];
	double	a;
	double	b;

	record->or = vec_sub(ray->origin, obj->pos);
	a = vec_dot(ray->dir, obj->rot);
	b = vec_dot(record->or, obj->rot);
	c[2] = vec_dot(ray->dir, ray->dir) - a * a;
	c[1] = 2 * (vec_dot(ray->dir, record->or) - (a * (b + 2 * obj->radius)));
	c[0] = vec_dot(record->or, record->or) - b * (b + 4 * obj->radius);
	return (rt_check_parab(c, ray, record));  
}

int     rt_hit_parabol(t_object *obj, t_ray *ray, t_hit *record)
{

	if (rt_init_params(obj, ray, record))
	{
		record->p = vec_ray(ray, record->t);
		record->n = rt_parabol_normal(ray, record, obj);
		return(1);
	}
  return(0);
} 