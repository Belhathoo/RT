
#include<rt.h>

void    cone_uv(t_object *o, t_hit *rec)
{
	t_vec d;

	d = vec_pro_k(vec_sub(rec->p, o->pos),  o->scale);
	d = vec(vec_dot(d, o->vec1), vec_dot(d, o->rot), vec_dot(d, o->vec2));
	rec->u = (atan2(d.x, d.z) + M_PI / (2.0 * M_PI));
	rec->v = d.y;
	rec->u = rec->u - floor(rec->u);
	rec->v = rec->v - floor(rec->v);
}

t_vec  normale_cone(t_object *o, t_ray *r, t_hit *rec)
{
	t_vec normale;

	rec->tmp = vec_pro_k(o->rot, (vec_dot(r->dir, o->rot) 
				* rec->t + vec_dot(rec->or, o->rot)));
	rec->tmp = vec_pro_k(rec->tmp, (1 + pow(tan(o->angle), 2)));
	normale = vec_unit(vec_sub(vec_sub(rec->p, o->pos), rec->tmp));
	return (normale);
}

int			rt_cone_params(t_object *o, t_ray *r, t_hit *rec)
{
	double min_sol;

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
	min_sol = (rec->t0 > EPS && rec->t0 < rec->t1) ?
		rec->t0 : rec->t1;
	if (min_sol < rec->closest && min_sol > MIN)
	{
		rec->t = min_sol;
		return (1);
	}
	return (0);
}

int			rt_hit_cone(t_object *o, t_ray *r, t_hit *rec)
{
	if (rt_cone_params(o, r, rec))
	{
		rec->p = vec_ray(r, rec->t);
		rec->n = normale_cone(o, r, rec);
		cone_uv(o, rec);
		return(1);
	}
	return(0);
}
