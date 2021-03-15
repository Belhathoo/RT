/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countword.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 00:52:41 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/31 04:35:18 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countword(const char *str, char c)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			while (str[i] != c && str[i] != '\0')
				i++;
			size++;
		}
	}
	return (size);
}
