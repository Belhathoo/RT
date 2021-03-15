/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 23:51:22 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/18 15:34:37 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*fraiche;
	unsigned int	i;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	while (s[i])
		i++;
	if (!(fraiche = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		fraiche[i] = f(i, s[i]);
		i++;
	}
	fraiche[i] = '\0';
	return (fraiche);
}
