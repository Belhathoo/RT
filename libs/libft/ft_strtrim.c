/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 07:59:41 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/17 01:49:40 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char			*copy;
	size_t			len;
	unsigned int	start;

	if (s == NULL)
		return (NULL);
	start = 0;
	while (s[start] == ' ' || s[start] == '\t' || s[start] == '\n')
		start++;
	if (!(start == ft_strlen(s)))
	{
		len = ft_strlen(s);
		len--;
		while (s[len] == ' ' || s[len] == '\t' || s[len] == '\n')
			len--;
		len++;
		copy = ft_strsub(s, start, (len - (size_t)start));
	}
	else
	{
		copy = malloc(sizeof(char));
		copy[0] = '\0';
	}
	return (copy);
}
