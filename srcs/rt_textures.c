/* ************************************************************************** */

#include <rt.h>

t_vec		rt_get_color_from_texture(t_object *o, double *u, double *v)
{
	int		i;
	int		j;
    int 	color;
	t_vec c;
	i = *u * o->txt.width;
	j = (1.0 - *v) * o->txt.height - 0.001;
	i = (i < 0) ? 0 : i;
	j = (j < 0) ? 0 : j;
	i = (i > o->txt.width - 1) ? o->txt.width - 1 : i;
	j = (j > o->txt.height - 1) ? o->txt.height - 1 : j;
	color = o->txt.buf[j * o->txt.width + i];

	c = rt_int_to_rgb(color);
    return(c);
}

int    remove_r(t_ray *ray, t_object *obj, t_hit *rec)
{
    t_vec vect;

     vect = rt_get_color_from_texture(obj, &rec->u, &rec->v);
	 if ((vect.z < vect.x && vect.y < vect.x))
	 {
		if (!ft_strcmp(obj->name, "plan"))
		     return (0);
		rec->p = vec_ray(ray, rec->t1);
		rec->n = vec_div_k(vec_sub(rec->p, obj->pos), -obj->size);
		sphere_uv(obj, rec);
		vect = rt_get_color_from_texture(obj, &rec->u, &rec->v);
		if ((vect.z < vect.x && vect.y < vect.x))
			 return 0;
		return (1);
	}

	return (1);
}

int    remove_g(t_ray *ray, t_object *obj, t_hit *rec)
{
    t_vec vect;

     vect = rt_get_color_from_texture(obj, &rec->u, &rec->v);
	 if ((vect.z < vect.y && vect.x < vect.y))
	 {
		  if (!ft_strcmp(obj->name, "plan"))
		     return (0);
		rec->p = vec_ray(ray, rec->t1);
		rec->n = vec_div_k(vec_sub(rec->p, obj->pos), -obj->size);
		sphere_uv(obj, rec);
		vect = rt_get_color_from_texture(obj, &rec->u, &rec->v);
		if ((vect.z < vect.y && vect.x < vect.y))
			 return 0;
		return (1);
	}

	return (1);
}

int    remove_b(t_ray *ray, t_object *obj, t_hit *rec)
{
    t_vec vect;
     vect = rt_get_color_from_texture(obj, &rec->u, &rec->v);
	 if ((vect.x < vect.z && vect.y < vect.z))
	 {
		 if (!ft_strcmp(obj->name, "plan"))
		     return (0);
		rec->p = vec_ray(ray, rec->t1);
		rec->n = vec_div_k(vec_sub(rec->p, obj->pos), -obj->size);
		sphere_uv(obj, rec);
		vect = rt_get_color_from_texture(obj, &rec->u, &rec->v);
		if ((vect.x < vect.z && vect.x < vect.z))
			 return 0;
		return (1);
	}

	return (1);
}

int			trans_texture(t_ray *ray, t_object *obj, t_hit *rec)
{
	if (obj->txt.is_trans == 1 && !remove_r(ray, obj, rec))
		return (0);
 else if (obj->txt.is_trans == 2 && !remove_g(ray, obj, rec))
		    return (0);
else if (obj->txt.is_trans == 3 && !remove_b(ray, obj, rec))
      return (0);
 else
   return (1);
}
