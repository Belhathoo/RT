/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:41:16 by belhatho          #+#    #+#             */
/*   Updated: 2021/01/20 11:41:18 by belhatho         ###   ########.fr       */
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

  printf("{{%s}}\n", tag_str);
  if (tag_str[0] == '/')
  {
    if (x->tags && ft_strncmp(&tag_str[1], x->tags->name, ft_strlen(x->tags->name)) == 0)
      return ;
    else
      xml_exit(x, ft_strdup("syntax error0"), EXIT_FAILURE);
  }
  xtag = x->tags;
  x->tags = xml_new_tag();
  x->tags->next = xtag;
  
  tag_str = xml_trim(tag_str, x);
  
  list = ft_strsplit(tag_str, '=');
  if (list == NULL)
		xml_exit(x, ft_strdup("empty tag"), EXIT_FAILURE);
/* 
      checking empty tag !!
      split = null > tag_str null, need another if
     // if (ft_strchr(tag_str, '=') == NULL)//)
	   // 	xml_exit(x, ft_strdup("empty tag"), EXIT_FAILURE);
 */   
  if (!(chr_str = ft_strchr(list[0], ' ')))
  	xml_exit(x, ft_strdup("syntax error1"), EXIT_FAILURE);

  x->tags->name = xml_trim(ft_strsub(list[0], 0, chr_str - list[0]), x);
  x->tags->attr = xml_new_attr();
  x->tags->attr->name = xml_trim(ft_strdup(chr_str), x);
  i = 0;
  curr_attr = x->tags->attr;
  while (list[++i])
  {
    if (list[i + 1] == NULL)
    {
      curr_attr->value = xml_set_attr(ft_strdup(list[i]), x);
      continue ;
    }
    else
      chr_str = ft_strrchr(list[i], ' ');

    if (!chr_str)
    	xml_exit(x, ft_strdup("syntax error01"), EXIT_FAILURE);

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
