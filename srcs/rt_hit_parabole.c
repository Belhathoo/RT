
#include <rt.h>

 int				rt_check_parab(double c[3], t_ray *ray, t_hit *rec)
{
	double	s[2];
	int		i;
	int		num;
    
	rec->t = rec->closest;
	i = -1;
	if ((num = rt_solve_quadric(c, s)))
	{
		while (++i < num)
		{
			if (s[i] >= MIN && s[i] < rec->t)
				rec->t = s[i];
		}
		if (rec->t >= MIN && rec->t < rec->closest)
		{
			rec->p = vec_ray(ray, rec->t);
			return (1);
		}
	}
	return (0);
}

int     rt_hit_parabol(t_object *obj, t_ray *ray, t_hit *record)
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
}