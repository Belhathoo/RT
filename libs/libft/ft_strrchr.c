/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 02:21:53 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/11 20:15:47 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	size;

	size = ft_strlen(s);
	if (*(char*)s == '\0' && size == 1)
		return ((char*)s);
	while (size)
	{
		if (*((char*)s + size) == (char)c)
			return ((char*)s + size);
		size--;
	}
	if (*((char*)s + size) == (char)c)
		return ((char*)s + size);
	return (NULL);
}
