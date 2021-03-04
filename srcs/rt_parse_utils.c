
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
	ft_free_twodim(&each);
	return (ret);
}

double   rt_ctod(char *str, t_rt *rt)
{
	double  ret;
	char    **each;

	each = ft_strsplit(str, ' ');
	if (!each || ft_twodimlen(each) != 1)
		rt_exit(rt, "must be One value for such data.\n", EXIT_FAILURE);
	ret= ft_atod(each[0]);
	ft_free_twodim(&each);
	return (ret);
}


t_texture   *rt_ctotxt(char *str, t_rt *rt)
{
	char        **each;
	t_texture   *txt;
	int bpp, size, endian;

	each = ft_strsplit(str, ' ');
	if (!each || ft_twodimlen(each) != 1)
		rt_exit(rt, "must be One value for texture data.\n", EXIT_FAILURE);
	txt = rt_init_txt(rt);
	txt->img = mlx_xpm_file_to_image(rt->mlx, each[0], &txt->width, &txt->height);
	if (!txt->img)
	{
		ft_free_twodim(&each);
		rt_exit(rt, "Texture: file unsupported", EXIT_FAILURE);
	}
	txt->buf = (int *)mlx_get_data_addr(txt->img, &bpp,  &size, &endian);	
	ft_free_twodim(&each);
	return (txt);
}

void	rt_get_repere(t_object *o)
{
	if (o->rot.x == 0.0 && o->rot.y == 0.0)
		o->vec1 = vec(1 / sqrt(2), 1 / sqrt(2), 0);
	else if (o->rot.x == 0.0 && o->rot.z == 0.0)
		o->vec1 = vec(1 / sqrt(2), 0, 1 / sqrt(2));
	else if (o->rot.z == 0.0 && o->rot.y == 0.0)
		o->vec1 = vec(0, 1 / sqrt(2), 1 / sqrt(2));
	else if (o->rot.x == 0.0)
		o->vec1 = vec(1, 0, 0);
	else if (o->rot.y == 0.0)
		o->vec1 = vec(0, 1, 0);
	else if (o->rot.z == 0.0)
		o->vec1 = vec(0, 0, 1);
	else if (fabs(o->rot.y) > 0.5) 
	{
        o->vec1 = vec_unit(vec_cross(o->rot, vec(1.0, 0.0, 0.0)));
	}
	else
		o->vec1 = vec_unit(vec(-(o->rot.y + o->rot.z) / o->rot.x, 1, 1));
	o->vec2 = (vec_cross(o->rot ,o->vec1));	
	
	// if ((vec_dot(vec_cross(o->rot, vec(0.0,1.0,0.0)), vec3(1.0))))
	// 	o->vec1 = vec_unit(vec_cross(o->rot, vec(0.0, 01.0, 0.0)));
	// if (!(vec_dot(vec_cross(o->rot, vec(1.0,0.0,0.0)), vec3(1.0))))
	// 	o->vec1 = vec_unit(vec_cross(o->rot, vec(1.0, 0.0, 0.0)));
	// if (!(vec_dot(vec_cross(o->rot, vec(0.0,0.0,01.0)), vec3(1.0))))
	// 	o->vec1 = vec_unit(vec_cross(o->rot, vec(0.0, 0.0, 01.0)));
}

