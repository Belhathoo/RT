#include <rt.h>

int			rt_hit_disc(t_object *o, t_ray *r, t_hit *rec)
{

	t_vec centre = o->pos;
	t_vec normal = o->rot;
	rec->t = ((vec_dot(normal, centre) - vec_dot(normal, r->origin)) / vec_dot(normal, r->dir));
	if (rec->t >= rec->closest || rec->t <= EPS)
		return (0);
	t_vec point = vec_sub(vec_ray(r, rec->t),centre);
	if (vec_length(point) >= o->radius)
		return(0);
	rec->p = vec_ray(r, rec->t);
	rec->n = vec_dot(r->dir, o->rot) > 0 ? vec_pro_k(o->rot, -1) : o->rot;
	plane_uv(rec, o);
	if (o->is_sliced == 1 && rt_one_slice(o, r, rec) == 0)
		return (0);
	if (o->txt.is_txt && o->txt.is_trans && !(trans_texture(r, o, rec)))
		return (0);
	return (1);
}
