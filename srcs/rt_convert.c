
# include <rt.h>

t_vec   rt_ctovec(char *str, t_rt *rt)
{
    char    **each;
    t_vec   ret;

    each = ft_strsplit(str, ' ');
    if (ft_twodimlen(each) != 3)
  		rt_exit(rt, "must be three values for Vectors data.\n", EXIT_FAILURE);
	ret.x = ft_atod(each[0]);
	ret.y = ft_atod(each[1]);
	ret.z = ft_atod(each[2]);
	printf("SPLIT:\t%s %s %s\nRET:\t%.2f %.2f %.2f\n",each[0], each[1], each[2], ret.x,ret.y, ret.z);
	ft_free_twodim(&each);
	return (ret);
}

double   rt_ctod(char *str, t_rt *rt)
{
    double  ret;
    char    **each;

    each = ft_strsplit(str, ' ');
    if (ft_twodimlen(each) != 1)
  		rt_exit(rt, "must be One value for such data.\n", EXIT_FAILURE);
	ret = ft_atod(each[0]);
	return (ret);
}

t_texture   *rt_ctotxt(char *str, t_rt *rt)
{
    char        **each;
    t_texture   *txt;
    int bpp, size, endian;

    each = ft_strsplit(str, ' ');
    if (!each && ft_twodimlen(each) != 1)
  		rt_exit(rt, "must be One value for texture data.\n", EXIT_FAILURE);
	txt = rt_init_txt(rt);
	if (!ft_strncmp(each[0], "damier", 6))
		txt->is_txt = 1;
	else
	{
		txt->img = mlx_xpm_file_to_image(rt->mlx, each[0], &txt->width, &txt->height);
		if (!txt->img)
			rt_exit(rt, "Texture: file unsupported", EXIT_FAILURE);
    	txt->buf = (int *)mlx_get_data_addr(txt->img, &bpp,  &size, &endian);
	}
	ft_free_twodim(&each);
	return (txt);
}