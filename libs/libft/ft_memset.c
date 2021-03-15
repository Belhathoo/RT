/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:09:47 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/12 01:03:01 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*dest;
	int		i;

	dest = (char*)b;
	i = 0;
	while (i < (int)len)
	{
		dest[i] = (unsigned char)c;
		i++;
	}
	b = (void*)dest;
	return (b);
}
