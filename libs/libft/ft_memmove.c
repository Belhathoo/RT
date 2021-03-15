/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 23:30:41 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/17 09:08:47 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*cas;

	cas = (char*)malloc(sizeof(char) * len);
	ft_memcpy(cas, src, len);
	ft_memcpy(dst, cas, len);
	return ((void*)dst);
}
