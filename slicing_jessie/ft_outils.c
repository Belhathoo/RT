/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 04:16:40 by belhatho          #+#    #+#             */
/*   Updated: 2020/12/09 04:16:49 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			ffmax(double a, double b)
{
	return ((a > b) ? a : b);
}

int				ft_twodimlen(char **twodim)
{
	int			s;

	s = 0;
	while (*twodim++)
		s++;
	return (s);
}

void			ft_free_twodim(char **to_free)
{
	int			i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

double			ft_atod(char *str)
{
	double		nbr;
	int			i;
	double		chfr;
	static int	signe;

	nbr = (double)ft_atoi(str);
	i = 0;
	chfr = 10;
	while ((str[i] == '\n') || (str[i] == ' ') || (str[i] == '\t')
			|| (str[i] == '\f') || (str[i] == '\v') || (str[i] == '\r'))
		i++;
	signe = str[i] == '-' ? 1 : 0;
	i = ((str[i] == '-') || (str[i] == '+')) ? i + 1 : i;
	while (str[i] && str[i++] != '.')
		i = i + 0;
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		nbr = nbr >= 0 && !signe ? nbr + (double)(str[i++] - 48) / chfr :
			nbr - (double)(str[i++] - 48) / chfr;
		chfr *= 10;
	}
	return (nbr);
}
