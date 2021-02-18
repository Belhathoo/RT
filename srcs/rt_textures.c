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



