# include <libxml.h>


// display tag & attr in error display !!!!

void xml_exit(t_xml *x, char *msg, int err)
{
  if (err == EXIT_FAILURE)
  {
    ft_putstr("libxml: ");
    ft_putendl(msg);
    // if (msg)
    //   free(msg);
    xml_close(x);
    exit(EXIT_FAILURE);
  }
  else
    ft_putendl(msg);
}

static void clean_tag(t_tag **tag)
{
  t_tag *curr_tag;
  t_attr *curr_attr;
  t_attr *tmp_attr;

  curr_tag = *tag;
  // printf("tagName: %s\n", curr_tag->name);
  free(curr_tag->name);
  curr_attr = curr_tag->attr;
  while (curr_attr != NULL)
  {
    tmp_attr = curr_attr->next;
    // printf("[\"%s\" = {%s}]  ", curr_attr->name, curr_attr->value);
    free(curr_attr->name);
    free(curr_attr->value);
    free(curr_attr);
    curr_attr = tmp_attr;
  }
  // printf("\n\n");
  free(curr_tag);
}

void xml_close(t_xml *x)
{
  t_tag *curr_tag;
  t_tag *tmp_tag;

  curr_tag = x->tags;
  while (curr_tag != NULL)
  {
    tmp_tag = curr_tag->next;
    clean_tag(&curr_tag);
    curr_tag = tmp_tag;
  }
  close(x->fd);
}