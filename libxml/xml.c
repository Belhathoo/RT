# include <libxml.h>

t_attr *xml_new_attr()
{
  t_attr *attr;

  attr = (t_attr*)malloc(sizeof(struct s_attr));
  attr->name = NULL;
  attr->value = NULL;
  attr->next = NULL;
  return  (attr);
}

t_tag *xml_new_tag()
{
  t_tag *tag;

  tag = (t_tag*)malloc(sizeof(t_tag));
  tag->name = NULL;
  tag->attr = NULL;
  tag->next = NULL;
  return (tag);
}

char *xml_set_attr(char *attr_str, t_xml *x)
{
  char *attr;
  int len;


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
  /* 
      closing tags !! 
  */
  // printf("\t[[%s]]\n", attr);
  if (len <= 2 || attr[0] != '\"' || attr[len - 1] != '\"')
    xml_exit(x, ft_strdup("syntax error; quotes"), EXIT_FAILURE);
  attr_str = ft_strsub(attr, 1, len - 2);
  free(attr); 
  return (attr_str);
}

char *xml_trim(char *attr_name, t_xml *x)
{
  char *name;

  name = attr_name;
  attr_name = ft_strtrim(attr_name);
  free(name);
  return (attr_name);
}

int xml_parse(t_xml *x)
{
  char *data;
  size_t  len;
  int i;
  int j;
  
  x->data = get_full_text(x->fd);
  len = ft_strlen(x->data);
  i = 1;
  if ((data = ft_strchr(x->data, '<')) == NULL)
    return (-1);
  while (data[i])
  {
    j = i;
    while (data[i] && data[i] != '>')
    {
      while (data[i] == '\t' || data[i] == '\n')
        data[i] = ' ';
      if (data[i] == '<')
        return (-1);
      i++;
    }
    i++;

    // recheck this if !!
    if (i >= len)
      break;
    xml_set_tag(ft_strsub(&data[j], 0, i - j - 1), x);
    while (data[i] && data[i] != '<')
    {
      if (data[i] == '>')
        return (-1);
      i++;
    }
    i++;
  }
  free(x->data);

  return (EXIT_SUCCESS);
}

t_xml *xml_init(const char *chemin)
{
  t_xml *x;
  char	*buf;

  x = (t_xml*)malloc(sizeof(t_xml));
	buf = NULL;
  x->tags = NULL;
	if ((x->fd = open(chemin, O_RDONLY)) == -1)
		xml_exit(x, ft_strjoin(chemin, ": no such file"), EXIT_FAILURE);
	if (read(x->fd, buf, 0) < 0)
		xml_exit(x, ft_strjoin(chemin, ": must be a file"), EXIT_FAILURE);
  if (get_next_line(x->fd, &buf) == 0)
    xml_exit(x, ft_strjoin(chemin, ": empty file"), EXIT_FAILURE);
  if (ft_strcmp(buf, "<!DOCTYPE xml>") != 0)
    xml_exit(x, ft_strjoin(chemin, ": document type <!DOCTYPE xml>"), EXIT_FAILURE);
  free(buf);
  x->tags = NULL;
  return (x);
}

