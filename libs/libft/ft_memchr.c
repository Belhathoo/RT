/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 08:26:45 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/23 00:40:01 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int		i;

	i = 0;
	while (i < (int)n)
	{
		if (*((unsigned char*)s + i) == (unsigned char)c)
			return ((char*)s + i);
		i++;
	}
	return (NULL);
}
