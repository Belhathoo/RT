/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:52:23 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/23 15:55:49 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	size_dst;
	size_t	size_src;
	size_t	i;
	size_t	j;

	size_dst = ft_strlen(dst);
	size_src = ft_strlen(src);
	if (size >= size_dst)
	{
		i = ft_strlen((const char*)dst);
		j = 0;
		while (i < size - 1 && src[j] != '\0')
		{
			dst[i] = *((char*)src + j);
			i++;
			j++;
		}
		dst[i] = '\0';
		return (size_dst + size_src);
	}
	else
		return (size_src + size);
	return (0);
}
