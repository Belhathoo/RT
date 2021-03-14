/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libxml.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:19:15 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/14 18:19:18 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBXML_H
# define LIBXML_H

# include <libft.h>
# include <fcntl.h>

# include <stdio.h>//delete me and add 2>/dev/null in makefile

typedef struct		s_attr
{
	char			*name;
	char			*value;
	struct s_attr	*next;
}					t_attr;

typedef struct		s_tag
{
	char			*name;
	t_attr			*attr;
	struct s_tag	*next;
}					t_tag;

typedef struct		s_xml
{
	int				fd;
	char			*data;
	t_tag			*tags;
	int				cam_nbr;
	int				obj_nbr;
}					t_xml;

int					xml_parse(t_xml *x);
t_xml				*xml_init(char *chemin);
t_tag				*xml_new_tag(void);
t_attr				*xml_new_attr(void);

void				xml_set_tag(char *tag_str, t_xml *x);
char				*xml_set_attr(char *attr_str, t_xml *x);
void				xml_check_tag(char *t_name, t_xml *x);
int					xml_check_attr(char *t_name, char *a_name);

char				*xml_trim(char *attr_name);

void				xml_exit(t_xml *x, char *m1, char *msg, int err);
void				xml_close(t_xml *x);

#endif
