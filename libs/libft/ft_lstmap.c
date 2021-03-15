/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 08:43:40 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/15 18:48:31 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*frais;

	if (lst != NULL)
	{
		frais = malloc(sizeof(void));
		frais = f(lst);
		frais->next = ft_lstmap(lst->next, f);
		return (frais);
	}
	return (NULL);
}
