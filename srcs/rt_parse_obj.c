/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:13:07 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/11 12:13:11 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int			rt_trans_txt(t_rt *rt, t_object *o, char *val)
{
	if (!ft_strcmp(val, "r") || !ft_strcmp(val, "R"))
		return (1);
	else if (!ft_strcmp(val, "g") || !ft_strcmp(val, "G"))
		return (2);
	else if (!ft_strcmp(val, "b") || !ft_strcmp(val, "B"))
		return (3);
	else
		rt_exit(rt, o->name, ": trans-txt R should be R || G | B."\
			, EXIT_FAILURE);
	return (-1);
}

int			rt_add_sizes(t_attr *attr, t_object *obj, t_rt *rt)
{
	if (!ft_strcmp(attr->name, "position"))
		obj->pos = rt_ctovec(attr->value, rt);
	else if (!ft_strcmp(attr->name, "direction"))
		obj->dir = vec_unit(rt_ctovec(attr->value, rt));
	else if (!ft_strcmp(attr->name, "translation"))
		obj->pos = vec_add(obj->pos, rt_ctovec(attr->value, rt));
	else if (!ft_strcmp(attr->name, "rotation"))
		obj->rot = rt_ctovec(attr->value, rt);
	else if (!ft_strcmp(attr->name, "color"))
		obj->col = rt_ctovec(attr->value, rt);
	else if (!ft_strcmp(attr->name, "radius"))
		obj->radius = rt_ctod(attr->value, rt);
	else if (!ft_strcmp(attr->name, "r"))
		obj->r = rt_ctod(attr->value, rt);
	else if (!ft_strcmp(attr->name, "size"))
		obj->size = rt_ctod(attr->value, rt);
	else if (!ft_strcmp(attr->name, "angle"))
		obj->angle = rt_ctod(attr->value, rt);
	else if (!ft_strcmp(attr->name, "height"))
		obj->height = rt_ctod(attr->value, rt);
	else if (!ft_strcmp(attr->name, "width"))
		obj->width = rt_ctod(attr->value, rt);
	else
		return (0);
	return (1);
}

int			rt_add_txt_noi(t_attr *attr, t_object *obj, t_rt *rt)
{
	if (!ft_strcmp(attr->name, "texture"))
		rt_ctotxt(attr->value, &obj->txt, rt);
	else if (!ft_strcmp(attr->name, "txt_mv1"))
		obj->txt.mv1 = rt_ctod(attr->value, rt);
	else if (!ft_strcmp(attr->name, "txt_mv2"))
		obj->txt.mv2 = rt_ctod(attr->value, rt);
	else if (!ft_strcmp(attr->name, "txt_trans"))
		obj->txt.is_trans = rt_trans_txt(rt, obj, attr->value);
	else if (!ft_strcmp(attr->name, "scale"))
		obj->scale = rt_ctod(attr->value, rt);
	else if (!ft_strcmp(attr->name, "noise") && (obj->noi.is_noise = 1))
		obj->noi.type = rt_add_noise(attr->value, rt);
	else if (!ft_strcmp(attr->name, "n_color"))
		obj->noi.col1 = rt_ctovec(attr->value, rt);
	else if (!ft_strcmp(attr->name, "n_color1"))
		obj->noi.col2 = rt_ctovec(attr->value, rt);
	else
		return (0);
	return (1);
}

int			rt_add_mat_sl(t_attr *attr, t_object *obj, t_rt *rt)
{
	if (!ft_strcmp(attr->name, "material"))
		obj->material = ft_strdup(attr->value);
	else if (!ft_strcmp(attr->name, "refl"))
		obj->refl = ft_clamping(rt_ctod(attr->value, rt));
	else if (!ft_strcmp(attr->name, "refr"))
		obj->refr = rt_ctod(attr->value, rt);
	else if (!ft_strcmp(attr->name, "slice_vec") && (obj->is_sliced = 1))
		obj->sl_vec = rt_ctovec(attr->value, rt);
	else if (!ft_strcmp(attr->name, "slice_pnt") && (obj->is_sliced = 1))
		obj->sl_pnt = rt_ctovec(attr->value, rt);
	else if (!ft_strcmp(attr->name, "slice_ax"))
		obj->sl_ax = rt_ax_parse(attr->value, obj, rt);
	else
		return (0);
	return (1);
}

void		rt_add_object(t_tag *tag, t_rt *rt)
{
	t_object	*obj;
	t_object	*tmp;

	obj = rt_init_object(rt);
	tmp = rt->scene->object;
	while (tag->attr)
	{
		if (!ft_strcmp(tag->attr->name, "name"))
		{
			obj->name = ft_strdup(tag->attr->value);
			rt_check_obj_name(obj, rt);
		}
		else if (rt_add_sizes(tag->attr, obj, rt) == 0)
		{
			if (rt_add_txt_noi(tag->attr, obj, rt) == 0)
				if (rt_add_mat_sl(tag->attr, obj, rt) == 0)
					rt_exit(rt, obj->name, ": Unknown attribut", EXIT_FAILURE);
		}
		tag->attr = tag->attr->next;
	}
	rt_check_obj(obj, rt);
	rt->scene->object = obj;
	obj->next = tmp;
}
