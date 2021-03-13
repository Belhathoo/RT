/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:53:22 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/13 17:51:30 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libxml.h>

void		xml_check_tag(char *t_name, t_xml *x)
{
	char	*str;

	str = t_name;
	// str = ft_strupcase(str);
	/*
	   Check for cam numbers!!
	   */
	if (!ft_strncmp(str, "Camera", 6) && x->cam_nbr > 1)
		xml_exit(x, ("Only One Camera Allowed !"), 1);
	if (!(!ft_strncmp(str, "Camera", 6) || !ft_strncmp(str, "Object", 6)\
		|| !ft_strncmp(str, "Neg_Object", 8) || !ft_strncmp(str, "Light", 5)\
		|| !ft_strncmp(str, "Option", 6)))
		xml_exit(x, ("Tag Unknown!"), 1);
}

int			xml_check_att_val(char *a_name)
{
	if (!ft_strcmp(a_name, "name") || !ft_strcmp(a_name, "position")\
		|| !ft_strcmp(a_name, "direction") || !ft_strcmp(a_name, "translation")\
		|| !ft_strcmp(a_name, "rotation") || !ft_strcmp(a_name, "radius")\
		|| !ft_strcmp(a_name, "r") || !ft_strcmp(a_name, "color")\
		|| !ft_strcmp(a_name, "texture") || !ft_strcmp(a_name, "txt_mv1")
		|| !ft_strcmp(a_name, "txt_mv2") | !ft_strcmp(a_name, "txt_trans")\
		|| !ft_strcmp(a_name, "noise") || !ft_strcmp(a_name, "slice_ax")\
		|| !ft_strcmp(a_name, "slice_vec") || !ft_strcmp(a_name, "slice_pnt")\
		|| !ft_strcmp(a_name, "material") || !ft_strcmp(a_name, "size")\
		|| !ft_strcmp(a_name, "height") || !ft_strcmp(a_name, "width")\
		|| !ft_strcmp(a_name, "angle") || !ft_strcmp(a_name, "scale")\
		|| !ft_strcmp(a_name, "refr") || !ft_strcmp(a_name, "refl")\
		|| !ft_strcmp(a_name, "n_color") || !ft_strcmp(a_name, "n_color1"))
		return (1);
	return (0);
}

int			xml_check_attr(char *t_name, char *a_name, t_xml *x)
{
	if (!ft_strcmp(t_name, "Object") && (xml_check_att_val(a_name)))
		return (1);
	else if (!ft_strcmp(t_name, "Camera") && (!ft_strcmp(a_name, "lookfrom")\
			|| !ft_strcmp(a_name, "lookat") || !ft_strcmp(a_name, "fov")))
		return (1);
	else if (!ft_strcmp(t_name, "Option") && (!ft_strcmp(a_name, "aa")\
			|| !ft_strcmp(a_name, "amb") || !ft_strcmp(a_name, "stereo")\
			|| !ft_strcmp(a_name, "filter")))
		return (1);
	else if (!ft_strcmp(t_name, "Light") && (!ft_strcmp(a_name, "type")\
		|| !ft_strcmp(a_name, "position") || !ft_strcmp(a_name, "intensity")\
			|| !ft_strcmp(a_name, "color") || !ft_strcmp(a_name, "direction")))
		return (1);
	else if (!ft_strcmp(t_name, "Neg_Object") && (!ft_strcmp(a_name, "name")\
		|| !ft_strcmp(a_name, "position") || !ft_strcmp(a_name, "direction")\
			|| !ft_strcmp(a_name, "angle") || !ft_strcmp(a_name, "rotation")\
			|| !ft_strcmp(a_name, "radius")))
		return (1);
	return (0);
}
