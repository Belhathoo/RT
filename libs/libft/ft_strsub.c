/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 19:02:28 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/21 00:49:20 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*fraiche;
	int				i;
	unsigned int	start_const;

	i = 0;
	start_const = start;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(&s[(size_t)start]) >= len)
	{
		if (!(fraiche = (char*)malloc((len + 1) * sizeof(char))))
			return (NULL);
		while ((size_t)start < len + start_const)
		{
			fraiche[i] = *((char*)s + (size_t)start);
			i++;
			start++;
		}
		fraiche[i] = '\0';
		return (fraiche);
	}
	else
		return (NULL);
}
