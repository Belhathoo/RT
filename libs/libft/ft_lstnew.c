/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:11:51 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/23 03:13:22 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *frais;

	frais = malloc(sizeof(t_list));
	if (!(frais))
		return (NULL);
	if (!(content))
	{
		frais->content = NULL;
		frais->content_size = 0;
	}
	else
	{
		frais->content = malloc(sizeof(void) * content_size);
		ft_memcpy(frais->content, content, content_size);
		frais->content_size = content_size;
	}
	frais->next = NULL;
	return (frais);
}
