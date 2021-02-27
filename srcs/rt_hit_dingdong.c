#include <rt.h>


t_vec			normal_dingdong(t_ray *ray, t_hit *rec, t_object *obj)
{
	t_vec	r;
  t_vec  normale;

	r = ray->dir;
	r = vec_sub(rec->p, obj->pos);
	normale.x = 2 * r.x;
    normale.y = 2 * r.y;
	normale.z = 3 * r.z * r.z - 2 * r.z;
	return (vec_unit(normale));
}

static int				rt_check_distance3(t_object *obj, double c[4], t_hit *rec, t_ray *ray)
{
	double	s[3];
	int		i;
	int		num;
	double		min_sol;
    
	min_sol = rec->closest;
	i = -1;
	if ((num = rt_solve_cubic(c, s)))
	{
		while (++i < num)
		{
			if (s[i] >= MIN && s[i] < min_sol)
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

static int				rt_init_params1(t_ray *ray, t_object *obj, t_hit *rec)
{
	
	double	c[4];

	rec->or = vec_sub(ray->origin, obj->pos);
	c[3] = (ray->dir.z * ray->dir.z * ray->dir.z);
	c[2] = (ray->dir.x * ray->dir.x) + (ray->dir.y * ray->dir.y) + (3 * ray->dir.z * ray->dir.z * rec->or.z) -
	(ray->dir.z * ray->dir.z);
	c[1] = 2 * (ray->dir.x * rec->or.x + ray->dir.y * rec->or.y - ray->dir.z * rec->or.z) +
	3 * (ray->dir.z * rec->or.z * rec->or.z);
	c[0] = (rec->or.x * rec->or.x) + (rec->or.y * rec->or.y) - (rec->or.z * rec->or.z) + (rec->or.z * rec->or.z * rec->or.z);
	return (rt_check_distance3(obj, c, rec, ray));
}

int				rt_hit_dingdong(t_ray *ray, t_object *obj, t_hit *rec)
{
	if (rt_init_params1(ray, obj, rec))
	{
		rec->p = vec_ray(ray, rec->t);
		rec->n = normal_dingdong(ray, rec, obj);
		return (1);
	}
	return (0);
}