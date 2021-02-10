
# include <rt.h>


t_ray		rt_ray(t_vec a, t_vec b)
{
	t_ray	r;

	r.origin = a;
	r.dir = b;
	return (r);
}

t_ray rt_get_ray(t_camera *p, double u, double v)
{
	return (rt_ray(p->origin, vec_unit(vec_sub(vec_add(p->lower_left_corner,
							vec_add(vec_pro_k(p->horizontal, u),
								vec_pro_k(p->vertical, v))), p->origin))));
}

t_vec	rt_noise(t_object *o, t_hit rec)
{
	t_vec	ret;

	if (o->noi.type == 1)
		return (rt_txt_damier(&rec));
}
