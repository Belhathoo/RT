
# include <rt.h>

t_vec		ft_rot_x(t_vec old, double theta)
{
	t_vec	new;

	new.x = old.x;
	new.y = old.y * cos(theta) - old.z * sin(theta);
	new.z = old.y * sin(theta) + old.z * cos(theta);
	return (new);
}

t_vec		ft_rot_y(t_vec old, double theta)
{
	t_vec	new;

	new.x = old.x * cos(theta) + old.z * sin(theta);
	new.y = old.y;
	new.z = -old.x * sin(theta) + old.z * cos(theta);
	return (new);
}

t_vec		ft_rot_z(t_vec old, double theta)
{
	t_vec	new;

	new.x = old.x * cos(theta) - old.y * sin(theta);
	new.y = old.x * sin(theta) + old.y * cos(theta);
	new.z = old.z;
	return (new);
}


// t_vect		project(t_vect direction, t_vect rotation)
// {
// 	t_vect new;
// 	double		previous_x;

// 	new.x = direction.x;
// 	new.y = direction.y * cos(rotation.x) + direction.z * sin(rotation.x);
// 	new.z = -direction.y * sin(rotation.x) + direction.z * cos(rotation.x);

// 	previous_x = new.x;
// 	new.x = new.x * cos(rotation.y) + new.z * sin(rotation.y);
// 	new.z = -new.x * sin(rotation.y) + new.z * cos(rotation.y);

// 	previous_x = new.x;
// 	new.x = new.x * cos(rotation.z) - new.y * sin(rotation.z);
// 	new.y = previous_x * sin(rotation.z) + new.y * cos(rotation.z);
// 	return (new);
// }

void	rt_rot_dir(t_vec *r, t_vec d)
{
/*
	check if dir = 0 0 0 (err sauf sphere || set default with a warning msg)
*/

	t_vec tmp;
	t_vec res;
	double	previous_x;
//if r.x=r.y=r.z skip
	tmp = *r;
	res.x = d.x;
	res.y = d.y * cos(tmp.x) + d.z * sin(tmp.x);
	res.z = -d.y * sin(tmp.x) + d.z * cos(tmp.x);

	previous_x = res.x;
	res.x = res.x *cos(tmp.y) + res.z * sin(tmp.y);
	res.z = -res.x * sin(tmp.y) + res.z * cos(tmp.y);

	previous_x = res.x;
	res.x = res.x * cos(tmp.z) - res.y * sin(tmp.z);
	res.y = previous_x * sin(tmp.z) + res.y * cos(tmp.z); 

	*r = res;
}


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
	// printf("SPLIT:\t%s %s %s\nRET:\t%.2f %.2f %.2f\n",each[0], each[1], each[2], ret.x,ret.y, ret.z);
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
    	txt->buf = (int *)mlx_get_data_addr(txt->img, &rt->bpp,  &rt->size, &rt->endian);
	}
	ft_free_twodim(&each);
	return (txt);
}