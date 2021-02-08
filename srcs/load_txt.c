
#include <rt.h>

int     rt_load_txt(t_rt *rt, t_object *o)
{
    int bpp;
    int endian;
    int size;
    
   o->txt->img = mlx_xpm_file_to_image(rt->mlx, "xpm/earth.xpm", &o->txt->width, &o->txt->height);
    if (!o->txt->img)
        printf("txt invalid");
        // return (-1);
    else
        o->txt->buf = (int *)mlx_get_data_addr(o->txt->img, &bpp, &size, &endian);
    return (1);
}