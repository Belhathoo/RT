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

char		*xml_set_attr(char *attr_str, t_xml *x)
{
	char	*attr;
	int		len;

	attr = NULL;
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
	{
		free(attr);
		xml_exit(x, "syntax error: ", "quotes", EXIT_FAILURE);
	}
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

int			xml_tg(char *data, int *k, char c, int x)
{
	char b;

	b = (c == '<') ? '>' : '<';
	while (data[*k] && data[*k] != c)
	{
		if (x == 1)
			(data[*k] == '\t' || data[*k] == '\n') ? data[*k] = ' ' : 0;
		if (data[*k] == b)
			return (-1);
		(*k)++;
	}
	return (1);
}

int			xml_parse(t_xml *x)
{
	char	*data;
	char	*tag;
	int		i;
	int		j;

	x->data = get_full_text(x->fd);
	if ((data = ft_strchr(x->data, '<')) == NULL)
		return (-1);
	
	i = 1;
	while (data[i])
	{
		j = i;
		if (xml_tg(data, &i, '>', 1) == -1)
			return (-1);
		if (!data[i] || i == j)
			return (-1);
		i++;
		tag = xml_trim(ft_strsub(&data[j], 0, i - j - 1));
		if ((ft_strlen(tag) == 0)\
			|| ((xml_set_tag(tag, x) && xml_tg(data, &i, '<', 0) == -1)))
			return (-1);
		(data[i]) ? i++ : 0;
	}
	ft_strdel(&x->data);
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
	if (ft_strcmp(buf, "<!DOCTYPE xml>") != 0)
		xml_exit(x, chemin, ": document type <!DOCTYPE xml>", EXIT_FAILURE);
	free(buf);
	return (x);
}
