
#include <rt.h>

void  torus_uv(t_object *o, t_hit *rec)
{
	t_vec p;
	double phi;
	double theta;
	double tmp;
	int scale = 1;

	p = vec_pro_k(vec_sub(rec->p, o->pos), 1.0);
	p = vec(vec_dot(p, o->vec1), vec_dot(p, o->rot), vec_dot(p, o->vec2));
	phi = atan2(p.z, p.x);
	tmp = p.x * p.x + p.z * p.z;
	theta = atan2(p.y, (sqrt(tmp))) - o->size;
	rec->u = 0.5 + phi / 2 * M_PI;
	rec->v = 0.5 + theta / 2 * M_PI;
	rec->u = rec->u - floor(rec->u);
    rec->v = rec->v - floor(rec->v);
	return;
}

t_vec		rt_torus_normal(t_object *obj, t_hit *rec, t_ray *ray)
{
	t_vec normal;
	double k;
	double m;
	t_vec	a;
	t_vec	v;

	a = ray->dir;
	v = vec_unit(obj->rot);
	k = vec_dot(vec_sub(rec->p, obj->pos), v);
	a = vec_sub(rec->p, vec_pro_k(v, k));
	m = obj->r * obj->r - k * k;
	m = sqrt(m);
	normal = vec_sub(rec->p, vec_sub(a, vec_pro_k(vec_sub(obj->pos, a),
	m / obj->size + m)));
	normal = vec_unit(normal);
   return (normal);
}

int     rt_hit_torus(t_object *obj, t_ray *ray, t_hit *record)
{
      t_coef c;
      double coe[5];

	record->or = vec_sub(ray->origin, obj->pos);
	c.m = vec_dot(ray->dir, ray->dir);
	c.n = vec_dot(ray->dir, record->or);
	c.o = vec_dot(record->or, record->or);
	c.p = vec_dot(ray->dir, obj->rot);
	c.q = vec_dot(record->or, obj->rot);
	coe[0] = c.o * c.o - 2 * c.o * (obj->size * obj->size + obj->r * obj->r) +
	4 * obj->size * obj->size * c.q * c.q + pow((obj->size * obj->size - obj->r * obj->r), 2);
	coe[1] = 4 * c.n * c.o - 4 * c.n * (obj->size * obj->size + obj->r * obj->r) +
	8 * obj->size * obj->size * c.p * c.q;
	coe[2] = 4 * c.n * c.n + 2 * c.m * c.o - 2 * c.m * (obj->size * obj->size +
	obj->r * obj->r) + 4 * obj->size * obj->size * c.p * c.p;
	coe[3] = 4 * c.m * c.n;
	coe[4] = c.m * c.m;
       return(rt_check_distance(obj, coe, record, ray));   
}

int				rt_check_distance(t_object *obj, double c[5], t_hit *rec, t_ray *ray)
{
	double	s[4];
	int		i;
	int		num;
    
	rec->t = rec->closest;
	i = -1;
	if ((num = rt_solve_quartic(c, s)))
	{
		while (++i < num)
		{
			if (s[i] >= MIN && s[i] < rec->t)
				rec->t = s[i];
		}
		if (rec->t >= MIN && rec->t < rec->closest)
		{
			rec->p = vec_ray(ray, rec->t);
			rec->n = rt_torus_normal(obj, rec, ray);
			torus_uv(obj, rec);
			return (1);
		}
	}
	return (0);
}

