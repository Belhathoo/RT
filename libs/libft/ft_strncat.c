/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 19:07:34 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/28 12:13:23 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = ft_strlen((const char*)s1);
	j = 0;
	while (*((const char*)s2 + j) != '\0' && j < n)
	{
		s1[i] = *((const char*)s2 + j);
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}
