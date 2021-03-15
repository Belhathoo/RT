/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 20:06:13 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/06/01 14:41:15 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t		chiffre(int n)
{
	size_t		chfr;
	size_t		one;

	chfr = 1;
	one = n;
	while ((one /= 10) != 0)
		chfr *= 10;
	return (chfr);
}

static	size_t		size(int n)
{
	size_t		i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while ((n /= 10) != 0)
		i++;
	return (i + 1);
}

char				*ft_itoa(int n)
{
	char		*fraiche;
	size_t		i;
	size_t		chfr;

	i = 0;
	if (!(fraiche = (char*)malloc((size(n) + 1) * sizeof(*fraiche))))
		return (NULL);
	if (n < 0)
	{
		n = -n;
		fraiche[i++] = '-';
	}
	if (n == -2147483648)
	{
		fraiche[i++] = '2';
		n = 147483648;
	}
	chfr = chiffre(n) * 10;
	while ((chfr /= 10) != 0)
	{
		fraiche[i++] = (n / chfr) + '0';
		n %= chfr;
	}
	fraiche[i] = '\0';
	return (fraiche);
}
