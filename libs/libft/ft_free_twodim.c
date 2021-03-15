/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_twodim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 02:21:27 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/07 00:22:38 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_free_twodim(char ***to)
{
	char	**to_free;
	int		i;

	i = 0;
	to_free = *to;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
	return (1);
}
