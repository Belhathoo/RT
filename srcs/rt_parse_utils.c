/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:40:36 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/11 15:40:40 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vec			rt_ctovec(char *str, t_rt *rt)
{
	char	**each;
	t_vec	ret;

	each = ft_strsplit(str, ' ');
	if (ft_twodimlen(each) != 3)
	{
		ft_free_twodim(&each);
		rt_exit(rt, 0, "must be three values for Vectors'/Colors' data."\
			, EXIT_FAILURE);
	}
	ret.x = ft_atod(each[0]);
	ret.y = ft_atod(each[1]);
	ret.z = ft_atod(each[2]);
	ft_free_twodim(&each);
	return (ret);
}

double			rt_ctod(char *str, t_rt *rt)
{
	double	ret;
	char	**each;

	each = ft_strsplit(str, ' ');
	if (!each || ft_twodimlen(each) != 1)
		rt_exit(rt, "", "must be One value for such data.\n", EXIT_FAILURE);
	ret = ft_atod(each[0]);
	ft_free_twodim(&each);
	return (ret);
}

t_texture		rt_ctotxt(char *str, t_rt *rt)
{
	char		**each;
	t_texture	txt;

	each = ft_strsplit(str, ' ');
	if (!each || ft_twodimlen(each) != 1)
	{
		ft_free_twodim(&each);
		rt_exit(rt, "", "must be One value for texture data.\n", EXIT_FAILURE);
	}
	txt.is_txt = 1;
	txt.buf = NULL;
	txt.img = NULL;
	txt.img = mlx_xpm_file_to_image(rt->mlx, each[0], &txt.width, &txt.height);
	if (!txt.img)
	{
		ft_free_twodim(&each);
		rt_exit(rt, "Texture: ", " file unsupported", EXIT_FAILURE);
	}
	txt.buf = (int *)mlx_get_data_addr(txt.img, &rt->bpp,\
		&rt->size, &rt->endian);
	ft_free_twodim(&each);
	return (txt);
}

void			rt_comp_obj(t_object *o, t_rt *rt)
{
	if (ft_strcmp(o->name, "cube") == 0)
		get_cube_compos(o, rt);
}

void			rt_get_repere(t_object *o)
{
	t_vec vup;

	// vup = vec(0.0, 1.0, 0.0);
	// if (is_yequal(vup, o->rot) == 1)
	// {
	// 	o->vec1 = vec(1.0, 0.0, 0.0);
	// 	o->vec2 = vec(0.0, 0.0, 1.0);
	// }
	// else
	// {
	// 	if (is_yequal(vup, o->rot) == -1)
	// 	{
	// 		o->vec1 = vec(-1.0, 0.0, 0.0);
	// 		o->vec2 = vec(0.0, 0.0, 1.0);
	// 	}
	// 	else
	// 	{
	// 		o->vec1 = vec_cross(vup, o->rot);
	// 		o->vec2 = vec_cross(o->vec1, o->rot);
	// 	}

	// }

	o->vec1 = vec_unit(vec_cross(o->rot, vec(0.0, 1.0, 0.0)));
	if (!(vec_dot(vec_cross(o->rot, vec(0.0, 1.0, 0.0)), vec3(1.0))))
		o->vec1 = vec_unit(vec_cross(o->rot, vec(1.0, 0.0, 0.0)));
	o->vec2 = (vec_cross(o->rot, o->vec1));
}
