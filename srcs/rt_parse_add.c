/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:15:42 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/11 12:21:06 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		rt_check_neg_obj_name(t_object *obj, t_rt *rt)
{
	char	*str;

	str = ft_strdup(obj->name);
	str = ft_strupcase(str);
	if (!ft_strcmp(str, "SPHERE"))
		obj->hit = rt_negative_sphere;
	else if (!ft_strcmp(str, "CYLINDER"))
		obj->hit = rt_negative_cylinder;
	else if (!ft_strcmp(str, "CONE"))
		obj->hit = rt_negative_cone;
	else
	{
		ft_strdel(&str);
		rt_exit(rt, obj->name, "unknown neg-obj!", EXIT_FAILURE);
	}
	ft_strdel(&str);
}

void		rt_add_negs(t_attr *attr, t_object *obj, t_rt *rt)
{
	if (!ft_strcmp(attr->name, "position"))
		obj->pos = rt_ctovec(attr->value, rt);
	else if (!ft_strcmp(attr->name, "direction"))
		obj->dir = vec_unit(rt_ctovec(attr->value, rt));
	else if (!ft_strcmp(attr->name, "rotation"))
		obj->rot = rt_ctovec(attr->value, rt);
	else if (!ft_strcmp(attr->name, "radius"))
		obj->size = rt_ctod(attr->value, rt);
	else if (!ft_strcmp(attr->name, "angle"))
		obj->angle = rt_ctod(attr->value, rt);
}

void		rt_add_neg_object(t_tag *tag, t_rt *rt)
{
	t_object	obj;

	if (rt->scene->is_neg != 0)
		rt_exit(rt, "Negative object", "Only one is allowed.", EXIT_FAILURE);
	obj = rt_init_neg_object();
	while (tag->attr)
	{
		if (!ft_strcmp(tag->attr->name, "name"))
		{
			obj.name = ft_strdup(tag->attr->value);
			rt_check_neg_obj_name(&obj, rt);
		}
		rt_add_negs(tag->attr, &obj, rt);
		tag->attr = tag->attr->next;
	}
	rt_check_neg_obj(&obj, rt);
	rt->scene->is_neg = 1;
	rt->scene->n_obj = obj;
}

int			rt_add_filter(char *val)
{
	if (!ft_strcmp(val, "sepia"))
		return (SEPIA);
	else if (!ft_strcmp(val, "negative"))
		return (NEGATIVE);
	else if (!ft_strcmp(val, "gray"))
		return (GRAY);
	else
		return (-1);
}

void		rt_add_option(t_tag *tag, t_rt *rt)
{
	while (tag->attr)
	{
		if (!ft_strcmp(tag->attr->name, "aa"))
			rt->scene->aa = (int)rt_ctod(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "amb"))
			rt->scene->ambient = rt_ctod(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "stereo"))
			rt->scene->stereo = rt_ctod(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "filter"))
			rt->filter = rt_add_filter(tag->attr->value);
		tag->attr = tag->attr->next;
	}
	if (rt->filter == -1)
		rt_exit(rt, "Option: fiter", "unknown.", EXIT_FAILURE);
	if (rt->scene->aa <= 0 || rt->scene->aa > 9)
		rt_exit(rt, "Option: aa", "should be positive & <= 9", EXIT_FAILURE);
	if (rt->scene->stereo < 0 || rt->scene->stereo > 9)
		rt_exit(rt, "Option: Stereo", "should be positive & < 10"\
				, EXIT_FAILURE);
	rt->scene->ambient = ft_clamping(rt->scene->ambient);
}
