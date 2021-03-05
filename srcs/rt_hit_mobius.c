
#include <rt.h>


 t_vec	 normal_mobius (t_vec *hit, t_object * obj)
{
	t_vec ret;

	ret. x = - 2 * obj->radius * hit-> z + 2 * hit-> x * hit-> y - 4 *
		hit-> x * hit-> z;
	ret. y = (obj->radius * obj->radius ) + hit-> x * hit-> x + 3 * hit-> y
		* hit-> y - 4 * hit-> y * hit-> z+ hit-> z* hit-> z;
	ret. z = (- 2 ) * obj->radius * hit-> x - 2 * hit-> x * hit-> x
		- 2 * hit-> y * hit-> y + 2 * hit-> y * hit-> z;
	return (vec_unit(ret));
}

static int				rt_init_mobius(t_object *o, t_vec p)
{
	t_vec	param;
	double	v;
	double	u;
	double k;
    
    u =  o->height + 5.0;
	v = atan2(p.y, p.x);

	if (sin(v / 2) != 0.0)
		u = p.z / sin(v / 2);
	else if (cos(v) != 0.0 && cos(v / 2) != 0.0)
		u = (p.x / cos(v) - o->radius) / cos(v / 2);
	else if (sin(v) != 0.0 && cos(v / 2) != 0.0)
		u = (p.y / sin(v) - o->radius) / cos(v / 2);
	if (!(u >= - o->height && u <= o->height))
	  return (0);
	param.x = (o->radius + u * cos(v / 2)) * cos(v);
	param.y = (o->radius + u * cos(v / 2)) * sin(v);
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
	rec->t= rec->closest;
	if ((h[1] = rt_solve_cubic(c, s)))
	{
		while (++h[0] < h[1])
		{
			if (s[h[0]] < rec->t && s[h[0]] > MIN)
			{
			    rec->t = s[h[0]];
				if (rt_init_mobius(o, vec_ray(ray, rec->t)))
				{
					h[2] = 1;
			
				}
			}
		}
		return (h[2] == 1);
	}
	return (0);
}

static int   rt_init_params(t_ray *ray, t_object *o, t_hit *rec)
{
	t_mobius m;

	m.a = ray->origin.x;
	m.b = ray->origin.y;
	m.c = ray->origin.z;
	m.d = ray->dir.x;
	m.e = ray->dir.y;
	m.f = ray->dir.z;
	m.radius = o->radius;
	rec->coef[0] = m.b * m.b * m.b - 2 * m.b * m.b * m.c + m.a * m.a * m.b
		+ m.b * m.c * m.c - m.b * m.radius * m.radius - 2 * m.a * m.a * m.c
		- 2 * m.a * m.c * m.radius;
	rec->coef[1] = 3 * m.e * m.b * m.b - 4 * m.e * m.b * m.c - 2 * m.f * m.b
		* m.b + 2 * m.d * m.a * m.b + 2 * m.f * m.b * m.c + m.e
		* m.a * m.a + m.e * m.c * m.c - m.e * m.radius * m.radius
		- 4 * m.d * m.a * m.c - 2 * m.f * m.a * m.a
		- 2 * m.f * m.a * m.radius - 2 * m.d * m.c * m.radius;
	rec->coef[2] = 3 * m.e * m.e * m.b - 2 * m.e * m.e * m.c + m.d * m.d *
m.b + m.f * m.f * m.b + 2 * m.d * m.e * m.a + 2 * m.e * m.f * m.c -
4 * m.d * m.f * m.a - 2 * m.d * m.f * m.radius - 2 * m.d * m.d * m.c - 4 *
m.e * m.f * m.b;
	rec->coef[3] = m.e * m.e * m.e + m.d * m.d * m.e + m.e * m.f * m.f
		- 2 * m.d * m.d * m.f - 2 * m.e * m.e * m.f;
	return (check_dist_mob(ray, rec, rec->coef, o)); 
}


int     rt_hit_mobius( t_object *o, t_ray *ray, t_hit *rec)
{
 
  if (rt_init_params(ray, o, rec))
  {
    rec->p = vec_ray(ray, rec->t);
	rec->n = normal_mobius(&rec->p, o);
    return (1);
  }
  return (0);
}