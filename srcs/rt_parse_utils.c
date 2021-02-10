
# include <rt.h>

// t_vec		ft_rot_x(t_vec old, double theta)
// {
// 	t_vec	new;

// 	new.x = old.x;
// 	new.y = old.y * cos(theta) - old.z * sin(theta);
// 	new.z = old.y * sin(theta) + old.z * cos(theta);
// 	return (new);
// }

// t_vec		ft_rot_y(t_vec old, double theta)
// {
// 	t_vec	new;

// 	new.x = old.x * cos(theta) + old.z * sin(theta);
// 	new.y = old.y;
// 	new.z = -old.x * sin(theta) + old.z * cos(theta);
// 	return (new);
// }

// t_vec		ft_rot_z(t_vec old, double theta)
// {
// 	t_vec	new;

// 	new.x = old.x * cos(theta) - old.y * sin(theta);
// 	new.y = old.x * sin(theta) + old.y * cos(theta);
// 	new.z = old.z;
// 	return (new);
// }


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

// void	rt_rot_dir(t_vec *r, t_vec d)
// {
// /*
// 	check if dir = 0 0 0 (err sauf sphere || set default with a warning msg)
// */

// 	t_vec tmp;
// 	t_vec res;
// 	double	previous_x;

// 	// tmp = *r;
// 	// if (tmp.x == 0 && tmp.y == 0 && tmp.z == 0)
// 	// {
// 	// 	*r = d;
// 	// 	return ;
// 	// }
// 	// res.x = d.x;
// 	// res.y = d.y * cos(tmp.x) + d.z * sin(tmp.x);
// 	// res.z = -d.y * sin(tmp.x) + d.z * cos(tmp.x);

// 	// previous_x = res.x;
// 	// res.x = res.x *cos(tmp.y) + res.z * sin(tmp.y);
// 	// res.z = -res.x * sin(tmp.y) + res.z * cos(tmp.y);

// 	// previous_x = res.x;
// 	// res.x = res.x * cos(tmp.z) - res.y * sin(tmp.z);
// 	// res.y = previous_x * sin(tmp.z) + res.y * cos(tmp.z); 

// 	// *r = res;
// 	*r = d;
// }


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

t_noise		rt_add_noise(char *val, t_rt *rt)
{
	t_noise	n;

	if (!ft_strcmp(val, "damier"))
		n.type = 1;

	n.is_noise = 1;
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
	//set_repere(o->rot, &o->vec1, &o->vec2);
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
	else
		o->vec1 = vec_unit(vec(-(o->rot.y + o->rot.z) / o->rot.x, 1, 1));
	o->vec2 = (vec_cross(o->rot ,o->vec1));	
}
