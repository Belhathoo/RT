/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 05:51:10 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/11 10:05:36 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int			i;
	int			nbr;
	int			signe;

	i = 0;
	nbr = 0;
	signe = 0;
	while ((str[i] == '\n') || (str[i] == ' ') || (str[i] == '\t') ||
			(str[i] == '\f') || (str[i] == '\v') || (str[i] == '\r'))
		i++;
	if (str[i] == '-')
		signe = 1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		nbr = (nbr * 10) + (str[i] - 48);
		i++;
	}
	if (signe == 1)
		return (-nbr);
	return (nbr);
}
