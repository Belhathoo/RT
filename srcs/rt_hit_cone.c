
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

t_vec   normale_cone(t_object *obj, t_ray *ray, t_hit *record, t_hit *rec1)
{
    t_vec normale;

	record->t = rec1->t;
	record->p = rec1->p;
	record->ray = ray;
    // normale = vec_pro_k(obj->rot, (vec_dot(ray->dir, vec_unit(obj->rot))
    // * rec1->t + vec_dot(rec1->or , vec_unit(obj->rot))));
	// normale = vec_pro_k(normale, -(1 + pow(tan(obj->size), 2)));
	// record->n = vec_unit(normale);
	record->n = vec_unit(vec_sub(vec_sub(rec1->p, obj->pos), rec1->tmp));
   return (normale);
}

int			rt_hit_cone(t_object *o, t_ray *r, t_hit *rec)
{
	
	t_hit rec1;
	
	rec1.or = vec_sub(r->origin, o->pos);
	rec1.coef[0] = vec_dot(r->dir, r->dir) - ((1 + pow(tan(o->angle), 2))
		* pow(vec_dot(r->dir, o->rot), 2));
	rec1.coef[1] = 2 * (vec_dot(r->dir, rec1.or) - ((1 + pow(tan(o->angle), 2))
			* vec_dot(rec1.or, o->rot) * vec_dot(r->dir, o->rot)));
	rec1.coef[2] = vec_dot(rec1.or, rec1.or) - ((1 + pow(tan(o->angle), 2)) // * rec1.or.z * rec1.or.z);
		* pow(vec_dot(rec1.or, o->rot), 2));
	rec1.delta = rec1.coef[1] * rec1.coef[1] - 4 * rec1.coef[0] * rec1.coef[2];
	if (rec1.delta < 0)
		return (0);
	rec1.t0 = (-rec1.coef[1] - sqrt(rec1.delta)) / (2 * rec1.coef[0]);
	rec1.t1 = (-rec1.coef[1] + sqrt(rec1.delta)) / (2 * rec1.coef[0]);
	rec1.t0 = (rec1.t0 > MIN && rec1.t0 < rec1.t1) ?
					rec1.t0 : rec1.t1;
	if (rec1.t0 < rec->closest && rec1.t0 > MIN)
	{
		rec1.t = rec1.t0;
		rec1.p = vec_ray(r, rec1.t);
		rec1.tmp = vec_pro_k(o->rot, (vec_dot(r->dir, o->rot) * rec1.t
					+ vec_dot(rec1.or, o->rot)));
		rec1.tmp = vec_pro_k(rec1.tmp, (1 + pow(tan(o->angle), 2)));
        normale_cone(o, r, rec, &rec1);
		cone_uv(o, rec);
        return (1);
	}
	return (0);
}

int			rt_hit_l_cone(t_object *o, t_ray *r, t_hit *rec)
{//hit_limited cone
	double	m;
	t_hit	rec1;
	//the max cap //o->height ]-oo,+oo[ //o->height < o->width

	rec1.or = vec_sub(r->origin, o->pos);
	rec1.coef[0] = vec_dot(r->dir, r->dir) - ((1 + pow(tan(o->angle), 2))
		* pow(vec_dot(r->dir, o->rot), 2));
	rec1.coef[1] = 2 * (vec_dot(r->dir, rec1.or) - ((1 + pow(tan(o->angle), 2))
			* vec_dot(rec1.or, o->rot) * vec_dot(r->dir, o->rot)));
	rec1.coef[2] = vec_dot(rec1.or, rec1.or) - ((1 + pow(tan(o->angle), 2)) // * rec1.or.z * rec1.or.z);
		* pow(vec_dot(rec1.or, o->rot), 2));
	rec1.delta = rec1.coef[1] * rec1.coef[1] - 4 * rec1.coef[0] * rec1.coef[2];
	if (rec1.delta < 0)
		return (0);
	rec1.t0 = (-rec1.coef[1] - sqrt(rec1.delta)) / (2 * rec1.coef[0]);
	rec1.t1 = (-rec1.coef[1] + sqrt(rec1.delta)) / (2 * rec1.coef[0]);
	(rec1.t0 < rec1.t1) ? 0 : ft_float_swap(&rec1.t0, &rec1.t1);
	m = vec_dot(r->dir, o->rot) * rec1.t0 + vec_dot(rec1.or, o->rot);
	if (m <= o->height || m >= o->width)
	{
		m = vec_dot(r->dir, o->rot) * rec1.t1 + vec_dot(rec1.or, o->rot);
		if (m <= o->height || m >= o->width)
			return (0);
		ft_float_swap(&rec1.t0, &rec1.t1);
	}
	rec1.t = rec1.t0;
	if (rec1.t < rec->closest && rec1.t > MIN)
	{
		rec1.p = vec_ray(r, rec1.t);
        normale_cone(o, r, rec, &rec1);
		rec->n = (rec1.t0 > rec1.t1) ? vec_pro_k(rec->n, -1) : rec->n;
		cone_uv(o, rec);
        return (1);
	}
	return (0);
}

