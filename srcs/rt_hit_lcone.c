
#include <rt.h>

int			rt_lcone_params(t_object *o, t_ray *r, t_hit *rec)
{
    //hit_limited cone
	//the max cap //o->height ]-oo,+oo[ //o->height < o->width
    double	m;
    double sol_min;

	rec->or = vec_sub(r->origin, o->pos);
	rec->coef[0] = vec_dot(r->dir, r->dir) - ((1 + pow(tan(o->angle), 2))
		* pow(vec_dot(r->dir, o->rot), 2));
	rec->coef[1] = 2 * (vec_dot(r->dir, rec->or) - ((1 + pow(tan(o->angle), 2))
			* vec_dot(rec->or, o->rot) * vec_dot(r->dir, o->rot)));
	rec->coef[2] = vec_dot(rec->or, rec->or) - ((1 + pow(tan(o->angle), 2))
		* pow(vec_dot(rec->or, o->rot), 2));
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta < 0)
		return (0);
	rec->t0 = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
	rec->t1 = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
	(rec->t0 < rec->t1) ? 0 : ft_float_swap(&rec->t0, &rec->t1);
	(rec->t0 <= EPS) ? ft_float_swap(&rec->t0, &rec->t1) : 0;
	m = vec_dot(r->dir, o->rot) * rec->t0 + vec_dot(rec->or, o->rot);
	if (m <= o->height || m >= o->width)
	{
		m = vec_dot(r->dir, o->rot) * rec->t1 + vec_dot(rec->or, o->rot);
		if (m <= o->height || m >= o->width)
			return (0);
		ft_float_swap(&rec->t0, &rec->t1);
	}
	 sol_min = rec->t0;
	if (sol_min < rec->closest && sol_min > MIN)
	{
        rec->t = sol_min;
	    return (1);
	}
	return (0);
}


int			rt_hit_lcone(t_object *o, t_ray *r, t_hit *rec)
{
    if (rt_lcone_params(o, r, rec))
    {
        rec->p = vec_ray(r, rec->t);
        rec->n =  normale_cone(o, r, rec);
		rec->n = (rec->t0 > rec->t1) ? vec_pro_k(rec->n, -1) : rec->n;
		cone_uv(o, rec);
        return (1);
    }
    return (0);
}