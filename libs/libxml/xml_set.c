/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:41:16 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/12 16:43:42 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libxml.h>

t_attr		*xml_new_attr(t_xml *x)
{
	t_attr *attr;

	if (!(attr = (t_attr*)malloc(sizeof(struct s_attr))))
		xml_exit(x, "xml", "cannot allocate!", EXIT_FAILURE);
	attr->name = NULL;
	attr->value = NULL;
	attr->next = NULL;
	return (attr);
}

t_tag		*xml_new_tag(t_xml *x)
{
	t_tag	*tag;

	if (!(tag = (t_tag*)malloc(sizeof(t_tag))))
		xml_exit(x, "xml", "cannot allocate!", EXIT_FAILURE);
	tag->name = NULL;
	tag->attr = NULL;
	tag->next = NULL;
	return (tag);
}

void		xml_affect_curent(char *chr_str, char ***lst, t_attr *curr_attr\
		, t_xml *x)
{
	char	**list;
	int		i;

	list = *lst;
	i = 0;
	while (list[++i])
	{
		if (xml_check_attr(x->tags->name, curr_attr->name) == 0)
			xml_exit(x, curr_attr->name, ": invalid attr.", EXIT_FAILURE);
		if (list[i + 1] == NULL)
		{
			curr_attr->value = xml_set_attr(ft_strdup(list[i]), x);
			continue ;
		}
		else
			chr_str = ft_strrchr(list[i], ' ');
		if (!chr_str && ft_free_twodim(lst))
			xml_exit(x, "", " syntax error", EXIT_FAILURE);
		curr_attr->value = xml_set_attr(\
				ft_strsub(list[i], 0, chr_str - list[i]), x);
		curr_attr->next = xml_new_attr(x);
		curr_attr->next->name = xml_trim(ft_strdup(chr_str));
		curr_attr = curr_attr->next;
	}
}

void		xml_affect_attrs(char ***lst, char *chr_str, t_xml *x)
{
	t_attr	*curr_attr;

	x->tags->attr = xml_new_attr(x);
	x->tags->attr->name = xml_trim(ft_strdup(chr_str));
	curr_attr = x->tags->attr;
	xml_affect_curent(chr_str, lst, curr_attr, x);
}

int			xml_set_tag(char *tag_str, t_xml *x)
{
	t_tag	*xtag;
	char	**list;
	char	*chr_str;

	if ((tag_str[0] == '/') && x->tags && ft_strncmp(&tag_str[1]\
				, x->tags->name, ft_strlen(x->tags->name)) == 0)
		return (1);
	else if (tag_str[0] == '/')
		xml_exit(x, x->tags->name, " syntax error", EXIT_FAILURE);
	xtag = x->tags;
	x->tags = xml_new_tag(x);
	x->tags->next = xtag;
	list = ft_strsplit(tag_str, '=');
	if ((!list || ft_twodimlen(list) <= 1 || ft_strchr(tag_str, '=') == NULL)
			&& ft_free_twodim(&list))
		xml_exit(x, "", "empty tag", EXIT_FAILURE);
	if (!(chr_str = ft_strchr(list[0], ' ')) && ft_free_twodim(&list))
		xml_exit(x, "", " syntax error", EXIT_FAILURE);
	x->tags->name = xml_trim(ft_strsub(list[0], 0, chr_str - list[0]));
	(!ft_strncmp(x->tags->name, "Camera", 6)) ? x->cam_nbr++ : 0;
	xml_check_tag(tag_str, x);
	xml_affect_attrs(&list, chr_str, x);
	free(tag_str);
	ft_free_twodim(&list);
	return (1);
}
