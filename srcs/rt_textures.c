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

int    tranc_txt(t_ray *ray, t_object *obj, t_hit *rec)
{
    t_vec vect;
	t_vec c;
   vect = rt_get_color_from_texture(obj, &rec->u, &rec->v);
   obj->txt.color = vec(0, 0, 1);
   c =  obj->txt.color;
	if ((vect.x < vect.z && vect.y < vect.z))
	{
		rec->p = vec_ray(ray, rec->t1);
		rec->n = vec_div_k(vec_sub(rec->p, obj->pos), -obj->size);
		sphere_uv(obj, rec);
		vect = rt_get_color_from_texture(obj, &rec->u, &rec->v);
		if ((vect.x < vect.z && vect.y < vect.z))
			 return 0;
		return (1);
	}
	return (1);
}