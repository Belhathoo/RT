/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:18:41 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/18 17:02:02 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*frch;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	frch = (char*)malloc(sizeof(char*) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!(frch))
		return (NULL);
	while (s1[i] != '\0')
	{
		frch[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		frch[i] = s2[j];
		i++;
		j++;
	}
	frch[i] = '\0';
	return (frch);
}
