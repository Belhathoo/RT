
#include <rt.h>

int     rt_load_txt(t_rt *rt, t_object *o)
{
    int bpp;
    int endian;
    int size;
   
   o->txt->filename = ft_strdup("xpm/earth.xpm"); // path
   printf("%s LOLO\n", o->txt->filename);
   o->txt->img = mlx_xpm_file_to_image(rt->mlx, o->txt->filename, &o->txt->width, &o->txt->height);
//    free(o->txt->filename);
    if (!o->txt->img)
        return (-1);
    else
        o->txt->buf = (int *)mlx_get_data_addr(o->txt->img, &bpp, &size, &endian);
    return (1);
}