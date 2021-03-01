
#include <rt.h>


int      cutt_plane(t_hit *rec, t_object *o)
{
	double largeur;
	double longeur;
	t_vec   pnt;

	pnt = vec_sub(rec->p, o->pos);

	if (o->name && !ft_strcmp(o->name, "rectangle"))
	{
		if ((fabs(vec_dot(pnt, o->vec1)) > o->width 
					|| fabs(vec_dot(pnt, o->vec2)) > o->height))
			return (0);
	}
	else
	{
		if ((fabs(vec_dot(pnt, o->vec1)) > o->size
					|| fabs(vec_dot(pnt, o->vec2)) > o->size))
			return (0);
	}
    return (1);
}


void			plane_uv(t_hit *rec, t_object *o)
{
  if (o->txt)
  {
	  o->txt->scale = 0.1;
	  rec->u = rt_frac(vec_dot(vec_pro_k(vec_sub(rec->p, o->pos), o->txt->scale), o->vec2));
	  rec->v = rt_frac(vec_dot(vec_pro_k(vec_sub(rec->p, o->pos), o->txt->scale), o->vec1));
	  return;
  }
  else 
  {
	 rec->u = rt_frac(vec_dot(vec_div_k(vec_sub(rec->p, o->pos), o->scale), o->vec2));
	 rec->v = rt_frac(vec_dot(vec_div_k(vec_sub(rec->p, o->pos), o->scale), o->vec1));
	 return;
  }
}

int     rt_hit_plan(t_object *o, t_ray *r, t_hit *rec)
{
	double  t;

	t = ((vec_dot(o->rot, o->pos) - vec_dot(o->rot, r->origin))
			/ vec_dot(o->rot, r->dir));
	if (t >= rec->closest || t <= MIN)
		return (0);
	rec->t = t;
	if (rec->negative[0] <= rec->t && rec->t <= rec->negative[1])
		return (0);
	rec->p = vec_ray(r, rec->t);
	rec->n = vec_dot(r->dir, o->rot) > 0 ? vec_pro_k(o->rot, -1) : o->rot;
	plane_uv(rec, o);
	return (1);
}

int         rt_hit_care(t_object *o, t_ray *ray, t_hit *rec)
{
	double  t;

	rec->t = ((vec_dot(o->rot, o->pos) - vec_dot(o->rot, ray->origin))
			/ vec_dot(o->rot, ray->dir));
	if (rec->t >= 1e-4 && rec->t < rec->closest)
	{
		rec->p = vec_ray(ray, rec->t);
		if (cutt_plane(rec, o) == 0)
			return (0);
		rec->n = vec_dot(ray->dir, o->rot) > 0? vec_pro_k(o->rot, -1) : o->rot;
		plane_uv(rec, o);
		return (1);
	}
	return (0);
}
