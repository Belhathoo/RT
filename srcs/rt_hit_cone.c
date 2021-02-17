
#include<rt.h>

void    cone_uv(t_object *o, t_hit *rec)
{
    t_vec d;
    double scale;

    scale = 0.5;
	d = vec_pro_k(vec_sub(rec->p, o->pos), scale);
	d = vec(vec_dot(d, o->vec1), vec_dot(d, o->rot), vec_dot(d, o->vec2));
	rec->u = (atan2(d.x, d.z) + M_PI / (2.0 * M_PI));
	rec->v = d.y;
    rec->u = rec->u - floor(rec->u);
    rec->v = rec->v - floor(rec->v);
}

t_vec   normale_cone(t_object *obj, t_ray *ray, t_hit *rec)
{
    t_vec normale;

    // normale = vec_pro_k(obj->rot, (vec_dot(ray->dir, vec_unit(obj->rot))
    // * rec1->t + vec_dot(rec1->or , vec_unit(obj->rot))));
	// normale = vec_pro_k(normale, -(1 + pow(tan(obj->size), 2)));
	// record->n = vec_unit(normale);
	rec->n = vec_unit(vec_sub(vec_sub(rec->p, obj->pos), rec->tmp));
   return (normale);
}

int			rt_hit_cone(t_object *o, t_ray *r, t_hit *rec)
{
	
	rec->or = vec_sub(r->origin, o->pos);
	rec->coef[0] = vec_dot(r->dir, r->dir) - ((1 + pow(tan(o->angle), 2))
		* pow(vec_dot(r->dir, o->rot), 2));
	rec->coef[1] = 2 * (vec_dot(r->dir, rec->or) - ((1 + pow(tan(o->angle), 2))
			* vec_dot(rec->or, o->rot) * vec_dot(r->dir, o->rot)));
	rec->coef[2] = vec_dot(rec->or, rec->or) - ((1 + pow(tan(o->angle), 2)) // * rec->or.z * rec->or.z);
		* pow(vec_dot(rec->or, o->rot), 2));
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta < 0)
		return (0);
	rec->t0 = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
	rec->t1 = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
	rec->t0 = (rec->t0 > EPS && rec->t0 < rec->t1) ?
					rec->t0 : rec->t1;
	if (rec->t0 < rec->closest && rec->t0 > EPS)
	{
		rec->t = rec->t0;
		rec->p = vec_ray(r, rec->t);
		rec->tmp = vec_pro_k(o->rot, (vec_dot(r->dir, o->rot) * rec->t
					+ vec_dot(rec->or, o->rot)));
		rec->tmp = vec_pro_k(rec->tmp, (1 + pow(tan(o->angle), 2)));
        rec->n = normale_cone(o, r, rec);
		cone_uv(o, rec);
        return (1);
	}
	return (0);
}

int			rt_hit_l_cone(t_object *o, t_ray *r, t_hit *rec)
{//hit_limited cone
	double	m;
	//the max cap //o->height ]-oo,+oo[ //o->height < o->width

	rec->or = vec_sub(r->origin, o->pos);
	rec->coef[0] = vec_dot(r->dir, r->dir) - ((1 + pow(tan(o->angle), 2))
		* pow(vec_dot(r->dir, o->rot), 2));
	rec->coef[1] = 2 * (vec_dot(r->dir, rec->or) - ((1 + pow(tan(o->angle), 2))
			* vec_dot(rec->or, o->rot) * vec_dot(r->dir, o->rot)));
	rec->coef[2] = vec_dot(rec->or, rec->or) - ((1 + pow(tan(o->angle), 2)) // * rec->or.z * rec->or.z);
		* pow(vec_dot(rec->or, o->rot), 2));
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta < 0)
		return (0);
	rec->t0 = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
	rec->t1 = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
	(rec->t0 < rec->t1) ? 0 : ft_float_swap(&rec->t0, &rec->t1);
	m = vec_dot(r->dir, o->rot) * rec->t0 + vec_dot(rec->or, o->rot);
	if (m <= o->height || m >= o->width)
	{
		m = vec_dot(r->dir, o->rot) * rec->t1 + vec_dot(rec->or, o->rot);
		if (m <= o->height || m >= o->width)
			return (0);
		ft_float_swap(&rec->t0, &rec->t1);
	}
	rec->t = rec->t0;
	if (rec->t < rec->closest && rec->t > MIN)
	{
		rec->p = vec_ray(r, rec->t);
        rec->n = normale_cone(o, r, rec);
		rec->n = (rec->t0 > rec->t1) ? vec_pro_k(rec->n, -1) : rec->n;
		cone_uv(o, rec);
        return (1);
	}
	return (0);
}

