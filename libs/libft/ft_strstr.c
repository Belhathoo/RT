/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 09:27:22 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/31 12:02:28 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check1(const char *str, const char *to_find, size_t i)
{
	while (to_find[i] != '\0')
	{
		if (to_find[i] != str[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strstr(const char *str, const char *to_find)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(str) >= ft_strlen(to_find))
	{
		if (to_find[0] == '\0')
			return ((char*)str);
		while (str[i] != '\0')
		{
			if (to_find[j] != str[i])
				i++;
			else if (check1(&str[i], &to_find[j], j) != 1)
				i++;
			else
				return ((char*)str + i);
		}
	}
	return (NULL);
}
