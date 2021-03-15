/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 01:55:33 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/05 08:53:10 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	size;

	size = ft_strlen(s);
	i = 0;
	while (i <= size)
	{
		if (*((char*)s + i) == (char)c)
			return ((char*)s + i);
		i++;
	}
	return (NULL);
}
