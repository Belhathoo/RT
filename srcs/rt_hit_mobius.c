
#include <rt.h>

static int				rt_init_mobius(t_object *o, t_vec p)
{
	t_vec	param;
	double	v;
	double	u;
	double	km;

	km = 3 * o->size / 4;
	v = atan2(p.y, p.x);
	u = km;
	if (sin(v / 2) != 0.0)
		u = p.z / sin(v / 2);
	else if (cos(v) != 0.0 && cos(v / 2) != 0.0)
		u = (p.x / cos(v) - o->size) / cos(v / 2);
	else if (sin(v) != 0.0 && cos(v / 2) != 0.0)
		u = (p.y / sin(v) - o->size) / cos(v / 2);
	if (!(u >= -km && u <= km))
		return (0);
	param.x = (o->size + u * cos(v / 2)) * cos(v);
	param.y = (o->size + u * cos(v / 2)) * sin(v);
	param.z = u * sin(v / 2);
	param = vec_sub(p, param);
	v = vec_lengthsquared(param);
	if (v > 0.000001 || v < -0.000001)
		return (0);
	return (1);
}

static int				check_dist_mob(t_ray *ray, t_hit *rec, double c[4], t_object *o)
{
	double      s[3];
	int			h[3];
	double	    sol_min;
	t_vec	p;

	h[2] = 0;
	h[0] = -1;
	sol_min = rec->closest;
	if ((h[1] = rt_solve_cubic(c, s)))
	{
		while (++h[0] < h[1])
		{
			if (s[h[0]] < sol_min && s[h[0]] > MIN)
			{
				sol_min = s[h[0]];
				rec->t = sol_min;
				p = vec_ray(ray, rec->t);;
				if (rt_init_mobius(o, p))
					h[2] = 1;
			}
		}
		return (h[2] == 1);
	}
	return (0);
}

static int   rt_init_params(t_ray *ray, t_object *o, t_hit *rec)
{
	rec->mob[0] = ray->origin.x;
	rec->mob[1] = ray->origin.y;
	rec->mob[2] = ray->origin.z;
	rec->mob[3] = ray->dir.x;
	rec->mob[4] = ray->dir.y;
	rec->mob[5] = ray->dir.z;
	rec->mob[6] = o->size;
	rec->coef[0] = rec->mob[1] * rec->mob[1] * rec->mob[1] - 2 * rec->mob[1] * rec->mob[1] * rec->mob[2] + rec->mob[0] * rec->mob[0] * rec->mob[1]
		+ rec->mob[1] * rec->mob[2] * rec->mob[2] - rec->mob[1] * rec->mob[6] * rec->mob[6] - 2 * rec->mob[0] * rec->mob[0] * rec->mob[2]
		- 2 * rec->mob[0] * rec->mob[2] * rec->mob[6];
	rec->coef[1] = 3 * rec->mob[4] * rec->mob[1] * rec->mob[1] - 4 * rec->mob[4] * rec->mob[1] * rec->mob[2] - 2 * rec->mob[5] * rec->mob[1]
		* rec->mob[1] + 2 * rec->mob[3] * rec->mob[0] * rec->mob[1] + 2 * rec->mob[5] * rec->mob[1] * rec->mob[2] + rec->mob[4]
		* rec->mob[0] * rec->mob[0] + rec->mob[4] * rec->mob[2] * rec->mob[2] - rec->mob[4] * rec->mob[6] * rec->mob[6]
		- 4 * rec->mob[3] * rec->mob[0] * rec->mob[2] - 2 * rec->mob[5] * rec->mob[0] * rec->mob[0]
		- 2 * rec->mob[5] * rec->mob[0] * rec->mob[6] - 2 * rec->mob[3] * rec->mob[2] * rec->mob[6];
	rec->coef[2] = 3 * rec->mob[4] * rec->mob[4] * rec->mob[1] - 2 * rec->mob[4] * rec->mob[4] * rec->mob[2] + rec->mob[3] * rec->mob[3] *
rec->mob[1] + rec->mob[5] * rec->mob[5] * rec->mob[1] + 2 * rec->mob[3] * rec->mob[4] * rec->mob[0] + 2 * rec->mob[4] * rec->mob[5] * rec->mob[2] -
4 * rec->mob[3] * rec->mob[5] * rec->mob[0] - 2 * rec->mob[3] * rec->mob[5] * rec->mob[6] - 2 * rec->mob[3] * rec->mob[3] * rec->mob[2] - 4 *
rec->mob[4] * rec->mob[5] * rec->mob[1];
	rec->coef[3] = rec->mob[4] * rec->mob[4] * rec->mob[4] + rec->mob[3] * rec->mob[3] * rec->mob[4] + rec->mob[4] * rec->mob[5] * rec->mob[5]
		- 2 * rec->mob[3] * rec->mob[3] * rec->mob[5] - 2 * rec->mob[4] * rec->mob[4] * rec->mob[5];
	return (check_dist_mob(ray, rec, rec->coef, o)); 
}


int     rt_hit_mobius(t_ray *ray, t_object *o, t_hit *rec)
{
  
  if (rt_init_params(ray, o, rec))
  {
    rec->p = vec_ray(ray, rec->t);
    return (1);
  }
  return (0);
}