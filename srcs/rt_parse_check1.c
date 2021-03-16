/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:30:21 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/11 11:30:26 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		rt_check_cam(t_camera c, t_rt *rt)
{
	if (c.lookat.x == c.lookfrom.x && c.lookat.y == c.lookfrom.y\
			&& c.lookat.z == c.lookfrom.z)
		rt_exit(rt, "camera::", " lookat & lookfrom should be different!"\
				, EXIT_FAILURE);
	if (c.fov < 4.0 || c.fov > 180)
		rt_exit(rt, "camera::", " fov is an angle [4-180]", EXIT_FAILURE);
}

int			rt_check_basic_obj(t_object *obj, char *str)
{
	if (!ft_strcmp(str, "SPHERE"))
		obj->hit = rt_hit_sphere;
	else if (!ft_strcmp(str, "CYLINDER"))
		obj->hit = rt_hit_cylinder;
	else if (!ft_strcmp(str, "PLAN"))
		obj->hit = rt_hit_plan;
	else if (!ft_strcmp(str, "CONE"))
		obj->hit = rt_hit_cone;
	else
		return (0);
	return (1);
}

int			rt_check_objs(t_object *obj, char *str)
{
	if (!ft_strcmp(str, "CUBE"))
		obj->hit = rt_hit_cube;
	else if (!ft_strcmp(str, "PARABOL"))
		obj->hit = rt_hit_parabol;
	else if (!ft_strcmp(str, "RECTANGLE"))
		obj->hit = rt_hit_care;
	else if (!ft_strcmp(str, "DISC"))
		obj->hit = rt_hit_disc;
	else if (!ft_strcmp(str, "L_CYLINDER"))
		obj->hit = rt_hit_lcylinder;
	else if (!ft_strcmp(str, "L_CONE"))
		obj->hit = rt_hit_lcone;
	else if (!ft_strcmp(str, "CUBE_TROUE"))
		obj->hit = rt_hit_cube_troue;
	else
		return (0);
	return (1);
}

void		rt_check_obj_name(t_object *obj, t_rt *rt)
{
	char	*str;

	if (obj->name == NULL)
		rt_exit(rt, "Object", " shoud have a name!", EXIT_FAILURE);
	str = ft_strdup(obj->name);
	str = ft_strupcase(str);
	if (!rt_check_basic_obj(obj, str))
	{
		if (!rt_check_objs(obj, str))
		{
			if (!ft_strcmp(str, "TORUS"))
				obj->hit = rt_hit_torus;
			else if (!ft_strcmp(str, "MOBIUS"))
				obj->hit = rt_hit_mobius;
			else
			{
				ft_strdel(&str);
				rt_exit(rt, obj->name, ": unknown obj!", EXIT_FAILURE);
			}
		}
	}
	ft_strdel(&str);
}

void		rt_check_neg_obj(t_object *o, t_rt *rt)
{
	if (o->name == NULL)
		rt_exit(rt, "", "Neg-Object shoud have a name!", EXIT_FAILURE);
	if (o->dir.x == 0 && o->dir.y == 0 && o->dir.z == 0)
		rt_exit(rt, "", "obj: direction vector is non-zero!", EXIT_FAILURE);
	if (o->radius <= 0.0)
		rt_exit(rt, "", "obj: radius should be positive", EXIT_FAILURE);
	if (o->angle <= 0.0 || o->angle > 179.0)
		rt_exit(rt, "", "obj: angle should be in ]0-180[", EXIT_FAILURE);
	o->angle = degtorad(o->angle) / 2;
	o->rot = rotation(o->dir, o->rot);
}
