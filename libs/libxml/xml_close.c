/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 19:01:07 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/13 19:01:08 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libxml.h>

void			xml_exit(t_xml *x, char *m1, char *msg, int err)
{
	if (err == EXIT_FAILURE)
	{
		ft_putstr("libxml: ");
		ft_putstr(m1);
		ft_putendl(msg);
		xml_close(x);
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_putstr(m1);
		ft_putendl(msg);
	}
}

static void		clean_tag(t_tag **tag)
{
	t_tag	*curr_tag;
	t_attr	*curr_attr;
	t_attr	*tmp_attr;

	curr_tag = *tag;
	free(curr_tag->name);
	curr_attr = curr_tag->attr;
	while (curr_attr != NULL)
	{
		tmp_attr = curr_attr->next;
		free(curr_attr->name);
		free(curr_attr->value);
		free(curr_attr);
		curr_attr = tmp_attr;
	}
	free(curr_tag);
}

void			xml_close(t_xml *x)
{
	t_tag	*curr_tag;
	t_tag	*tmp_tag;

	curr_tag = x->tags;
	while (curr_tag != NULL)
	{
		tmp_tag = curr_tag->next;
		clean_tag(&curr_tag);
		curr_tag = tmp_tag;
	}
	if (x->data)
		ft_strdel(&x->data);
	close(x->fd);
}
