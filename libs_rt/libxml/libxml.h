#ifndef XML_H
# define XML_H

# include <libft.h>
# include <fcntl.h>
# include <stdio.h>//delete me and add 2>/dev/null in makefile

typedef struct	s_attr
{
	char			*name;
	char			*value;
  struct s_attr 	*next;
}				t_attr;

typedef struct	s_tag
{
	char *name;
	t_attr *attr;
  struct s_tag *next;
}				t_tag;

typedef struct	s_xml
{
	int			fd;
	char	*data;
	t_tag			*tags;
}				t_xml;

int		xml_parse(t_xml *x);
t_xml	*xml_init(const char *chemin);
t_tag	*xml_new_tag();
t_attr	*xml_new_attr();

void	xml_set_tag(char *tag_str, t_xml *x);
char	*xml_set_attr(char *attr_str, t_xml *x);

char	*xml_trim(char *attr_name, t_xml *x);

void	xml_exit(t_xml *x, char *msg, int err);
void	xml_close(t_xml *x);

#endif