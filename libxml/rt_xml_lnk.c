
# include "../../rt/rt.h"
# include <libxml.h>
void  xml_to_rt(t_xml *x, t_rt *rt)
{
  /*
    function that looks for s pecific tag
  */
  while(x->tags)
  {
    
  }
}

void rt_parser(t_rt *rt, char **argv)
{
  t_xml *x;

  if (!(x = (struct s_xml *)malloc(sizeof(struct s_xml))))
    rt_exit(rt, "malloc Fail!", EXIT_FAILURE);
  xml_parse(x);
  // if (x_parse== -1) err. (check redo in main libxml)
  xml_to_rt(x, rt);
}