/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:26:06 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/13 16:26:12 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libxml.h>

t_attr		*xml_new_attr(void)
{
	t_attr *attr;

	attr = (t_attr*)malloc(sizeof(struct s_attr));
	attr->name = NULL;
	attr->value = NULL;
	attr->next = NULL;
	return (attr);
}

t_tag		*xml_new_tag(void)
{
	t_tag	*tag;

	tag = (t_tag*)malloc(sizeof(t_tag));
	tag->name = NULL;
	tag->attr = NULL;
	tag->next = NULL;
	return (tag);
}

char		*xml_set_attr(char *attr_str, t_xml *x)
{
	char	*attr;
	int		len;

	attr = ft_strtrim(attr_str);
	len = ft_strlen(attr);
	if (attr[len - 1] == '/')
	{
		attr[len - 1] = '\0';
		attr_str = ft_strtrim(attr);
		free(attr);
		attr = attr_str;
		len = ft_strlen(attr);
	}
	if (len <= 2 || attr[0] != '\"' || attr[len - 1] != '\"')
		xml_exit(x, "syntax error: ", "quotes", EXIT_FAILURE);
	attr_str = ft_strsub(attr, 1, len - 2);
	free(attr);
	return (attr_str);
}

char		*xml_trim(char *attr_name)
{
	char	*name;

	name = attr_name;
	attr_name = ft_strtrim(attr_name);
	free(name);
	return (attr_name);
}

int			xml_parse(t_xml *x)
{
	char	*data;
	char	*tag;
	int		i;
	int		j;

	x->data = get_full_text(x->fd);
	i = 1;
	if ((data = ft_strchr(x->data, '<')) == NULL)
		return (-1);
	while (data[i])
	{
		j = i;
		while (data[i] && data[i] != '>')
		{
			(data[i] == '\t' || data[i] == '\n') ? data[i] = ' ' : 0;
			if (data[i] == '<')
				return (-1);
			i++;
		}
		if (!data[i] || i == j)
			return (-1);
		i++;
		tag = ft_strsub(&data[j], 0, i - j - 1);
		tag = xml_trim(tag);
		if (ft_strlen(tag) == 0)
			xml_exit(x, "", "< / > error", EXIT_FAILURE);
		xml_set_tag(tag, x);
		while (data[i] && data[i] != '<')
		{
			if (data[i] == '>')
				return (-1);
			i++;
		}
		(data[i]) ? i++ : 0;
	}
	free(x->data);
	return (EXIT_SUCCESS);
}

t_xml		*xml_init(char *chemin)
{
	t_xml	*x;
	char	*buf;

	buf = NULL;
	if (!(x = (t_xml*)malloc(sizeof(t_xml))))
		xml_exit(x, "", ":Cannot allocate", EXIT_FAILURE);
	x->data = NULL;
	x->tags = NULL;
	x->cam_nbr = 0;
	x->obj_nbr = 0;
	if ((x->fd = open(chemin, O_RDONLY)) == -1)
		xml_exit(x, chemin, ": no such file", EXIT_FAILURE);
	if (read(x->fd, buf, 0) < 0)
		xml_exit(x, chemin, ": must be a file", EXIT_FAILURE);
	if (get_next_line(x->fd, &buf) == 0)
		xml_exit(x, chemin, ": empty file", EXIT_FAILURE);
	if (ft_strncmp(buf, "<!DOCTYPE xml>", 14) != 0)
		xml_exit(x, chemin, ": document type <!DOCTYPE xml>", EXIT_FAILURE);
	free(buf);
	return (x);
}
