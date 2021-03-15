
#include <rt.h>

void	cone_uv(t_object *o, t_hit *rec)
{
	t_vec	d;
    float	r;
	
	r = (float)o->txt.height / (float)o->txt.width;
	d = vec_sub(rec->p, o->pos);
	d = vec_add(d, vec_pro_k(o->rot, o->txt.mv1));
	d = ft_rot_vec(d, o->rot, o->txt.mv2); 
	d = vec(vec_dot(d, o->vec2), vec_dot(d, o->rot), vec_dot(d, o->vec1));
	rec->u= (atan2(d.x, d.z) + (M_PI )) / (2*M_PI);
	rec->v= (d.y / o->radius) * r;
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
	(rec->t0 > rec->t1) ? ft_float_swap(&rec->t0, &rec->t1) : 0;
	(rec->t0 <= EPS) ? ft_float_swap(&rec->t0, &rec->t1) : 0;
	return (1);
}

int			rt_hit_cone(t_object *o, t_ray *r, t_hit *rec)
{
	if (rt_cone_params(o, r, rec))
	{
		if (o->is_sliced == 1 && rt_slicing(o, r, rec) == 0)
			return (0);
		if (negative(rec) == 0)
			return (0);
		if (rec->t < rec->closest && rec->t > EPS)
		{
			rec->p = vec_ray(r, rec->t);
			if (rec->tx == 1)
				rec->n = vec_pro_k(o->sl_vec, -1);
			else if (rec->is_n == 1 && rec->t == rec->negative[1])
				rec->n = rec->negative_normal;
			else if (rec->t1 <= EPS)
				rec->n = normale_cone(o, r, rec);
			else
				rec->n = normale_cone(o, r, rec);
			cone_uv(o, rec);
			if (o->txt.is_txt && o->txt.is_trans && !(trans_texture(r, o, rec)))
	     	  return(0);
			return (1);
		}
	}
	return(0);
}
