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

# include <libxml.h>

void  xml_set_tag(char *tag_str, t_xml *x)
{
	t_tag *xtag;
	t_attr *curr_attr;
	char **list;
	char *chr_str;
	int i;

	if (tag_str[0] == '/')
	{
		if (x->tags && ft_strncmp(&tag_str[1], x->tags->name, ft_strlen(x->tags->name)) == 0)
			return ;
		else
			xml_exit(x, ("syntax error0"), EXIT_FAILURE);
	}
	xtag = x->tags;
	x->tags = xml_new_tag();
	x->tags->next = xtag;

	tag_str = xml_trim(tag_str, x);


	list = ft_strsplit(tag_str, '='); 

	if (!list && (ft_twodimlen(list) <= 1 || ft_strchr(tag_str, '=') == NULL))
		xml_exit(x, ("empty tag"), EXIT_FAILURE);
	if (!(chr_str = ft_strchr(list[0], ' ')))
		xml_exit(x, ("syntax error1"), EXIT_FAILURE);

	/* 
	   checking empty tag !!
	   split = null > tag_str null, need another if
	   */


	/*    checking attr names   */

	x->tags->name = xml_trim(ft_strsub(list[0], 0, chr_str - list[0]), x);
	if (!ft_strncmp(x->tags->name, "Camera", 6))
		x->cam_nbr++;
	if (!ft_strcmp(x->tags->name, "Object"))
		x->obj_nbr++;

	xml_check_tag(tag_str, x); ///CHECK!!
	/* affect attr */
	x->tags->attr = xml_new_attr();
	x->tags->attr->name = xml_trim(ft_strdup(chr_str), x);

	i = 0;
	curr_attr = x->tags->attr;
	while (list[++i])
	{
		if (ft_strchr(list[i], '\"') == NULL || !ft_strncmp(list[i], "\"\"", 2))
			xml_exit(x, (" empty attr."), EXIT_FAILURE);

		/*    checking attr names   */
		if (xml_check_attr(x->tags->name, curr_attr->name, x) == 0)
			xml_exit(x, ft_strjoin(curr_attr->name, "; invalid attr."), EXIT_FAILURE);

		if (list[i + 1] == NULL)
		{
			curr_attr->value = xml_set_attr(ft_strdup(list[i]), x);
			continue ;
		}
		else
			chr_str = ft_strrchr(list[i], ' ');

		if (!chr_str)
			xml_exit(x, (" syntax error01"), EXIT_FAILURE);

		curr_attr->value = xml_set_attr(ft_strsub(list[i], 0, chr_str - list[i]), x);
		if (list[i + 1] == NULL)
			break ;
		curr_attr->next = xml_new_attr();
		curr_attr->next->name = xml_trim(ft_strdup(chr_str), x);
		curr_attr = curr_attr->next;
	}
	free(tag_str);
	ft_free_twodim(&list);
}
