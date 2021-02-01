/* ************************************************************************** */

#include <rt.h>

t_vec		rt_get_color_from_texture(t_object *o, double *u, double *v)
{
	int		i;
	int		j;
    int 	color;
	t_vec c;
	i = *u * o->txt->width;
	j = (1.0 - *v) * o->txt->height - 0.001;
	i = (i < 0) ? 0 : i;
	j = (j < 0) ? 0 : j;
	i = (i > o->txt->width - 1) ? o->txt->width - 1 : i;
	j = (j > o->txt->height - 1) ?o->txt->height - 1 : j;
	color = o->txt->buf[j * o->txt->width + i];
	c = rt_int_to_rgb(color);
    return(c);
}

t_vec		rt_txt_damier(t_hit *rec)
{
	int pro1;
	int pro2;
	
	if (ft_strcmp(rec->curr_obj->name, "TORUS") == 0)
		return (torus_txt(rec));
	pro1 = floor(rec->u * 14);
	pro2 = floor(rec->v * 14);
	if (fabs(fmod(pro1, 2)) == fabs(fmod(pro2, 2)))
		return (vec(0, 0, 0));
	return (vec(1, 1, 1));
	
}

t_vec  torus_txt(t_hit *rec)
{
	int i;
	int j;
    int oddity;

	i = (int)(10 * rec->u);
	j = (int)(10 * rec->v);
	if ((i & 0x01) == (j & 0x01))
		oddity = 1;
	else
		oddity = 0;
	if ((((10 * rec->u - i) < 0.2) && oddity) || ((10 * rec->v - j) < 0.2))
	  return (vec(0, 0, 0));
	else 
	  return (vec(1, 1, 1));
}