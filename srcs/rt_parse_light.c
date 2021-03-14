/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:48:16 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/14 19:05:54 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int			rt_check_light_type(char *val)
{
	if (!ft_strcmp(val, "point"))
		return (PT_LIGHT);
	else if (!ft_strcmp(val, "parallel"))
		return (PL_LIGHT);
	else
		return (-1);
}

void		rt_check_lights(t_light *l, t_rt *rt)
{
	if (l->dir.x == 0 && l->dir.y == 0 && l->dir.z == 0)
		rt_exit(rt, "light: ", "direction vector is non-zero!", EXIT_FAILURE);
	if ((l->intensity = ft_clamping(l->intensity)) == 0.0)
		rt_exit(rt, "light", "intensity is a positive number ]0-1]"\
				, EXIT_FAILURE);
	if (l->col.x == 0.0 && l->col.y == 0.0 && l->col.z == 0.0)
		rt_exit(rt, "light", "no light have black color", EXIT_FAILURE);
	if (l->type == -1)
		rt_exit(rt, "light: ", "unknown type", EXIT_FAILURE);
	rt_adjustment(&l->col);
	l->intensity = ft_clamping(l->intensity);
}

void		rt_add_light(t_tag *tag, t_rt *rt)
{
	t_light *l;
	t_light	*tmp;

	l = rt_init_light(rt);
	tmp = rt->scene->light;
	while (tag->attr)
	{
		if (!ft_strcmp(tag->attr->name, "type"))
			l->type = rt_check_light_type(tag->attr->value);
		else if (!ft_strcmp(tag->attr->name, "position"))
			l->pos = rt_ctovec(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "direction"))
			l->dir = vec_unit(rt_ctovec(tag->attr->value, rt));
		else if (!ft_strcmp(tag->attr->name, "intensity"))
			l->intensity = rt_ctod(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "color"))
			l->col = rt_ctovec(tag->attr->value, rt);
		tag->attr = tag->attr->next;
	}
	rt_check_lights(l, rt);
	rt->scene->light = l;
	l->next = tmp;
}

void		rt_set_coef_ann(t_object *o)
{
	if (!ft_strcmp(o->material, "diamond"))
		o->mat = (t_material){vec3(0.8), vec3(0.4), vec3(0.2)\
						, 146.80, 0.0, 2.41};
	else if (!ft_strcmp(o->material, "ice"))
		o->mat = (t_material){vec3(0.8), vec3(0.2), vec3(0.2), 10, 0.0, 1.331};
	else if (!ft_strcmp(o->material, "glass"))
		o->mat = (t_material){vec3(0.25), vec3(0.2), vec3(0.5), 70, 0.0, 1.50};
	else if (!ft_strcmp(o->material, "water"))
		o->mat = (t_material){vec3(0.5), vec3(0.1), vec3(0.05), 20, 0.0, 1.20};
}

void		rt_set_coef(t_object *o)
{
	o->mat = (t_material){vec3(0.70), vec3(0.80), vec3(0.30), 80.0, 0.0, 0.0};
	if (o->material)
	{
		if (!ft_strcmp(o->material, "bl_plastic"))
			o->mat = (t_material){vec3(0.20), vec3(0.21), vec3(0.5)\
			, 32, 0.0, 0.0};
		else if (!ft_strcmp(o->material, "cu"))
			o->mat = (t_material){vec(0.33, 0.23, 0.02)\
					, vec(0.78, 0.568, 0.113), vec(0.99, 0.94, 0.807)\
						, 27.897, 0.0, 0.0};
		else if (!ft_strcmp(o->material, "chrome"))
			o->mat = (t_material){vec3(0.25), vec3(0.4), vec3(0.774)\
			, 76.70, 0.0, 0.0};
		else if (!ft_strcmp(o->material, "gold"))
			o->mat = (t_material){vec(0.24, 0.199, 0.074)\
		, vec(0.75, 0.606, 0.226), vec(0.628, 0.555, 0.3660), 51.2, 0.55, 0.0};
		else if (!ft_strcmp(o->material, "mirror"))
			o->mat = (t_material){vec3(1.0), vec3(1.0), vec3(1), 100, 1.0, 0.0};
		else if (!ft_strcmp(o->material, "al"))
			o->mat = (t_material){vec3(0.92), vec3(0.999), vec3(0.8)\
							, 25, 0.150, 0.0};
		else
			rt_set_coef_ann(o);
	}
}
