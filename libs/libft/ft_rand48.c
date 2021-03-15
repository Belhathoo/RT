/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand48.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 00:22:20 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/19 21:18:48 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_dorand48(unsigned short xseed[3])
{
	unsigned long			accu;
	unsigned short			temp[2];

	accu = (unsigned long)(0xe66d) * (unsigned long)xseed[0] +
		(unsigned long)(0x000b);
	temp[0] = (unsigned short)accu;
	accu >>= sizeof(unsigned short) * 8;
	accu += (unsigned long)(0xe66d) * (unsigned long)xseed[1] +
		(unsigned long)(0xdeec) * (unsigned long)xseed[0];
	temp[1] = (unsigned short)accu;
	accu >>= sizeof(unsigned short) * 8;
	accu += (0xe66d) * xseed[2] + (0xdeec) * xseed[1] +
		(0x0005) * xseed[0];
	xseed[0] = temp[0];
	xseed[1] = temp[1];
	xseed[2] = (unsigned short)accu;
}

static	double	ft_erand48(unsigned short xseed[3])
{
	ft_dorand48(xseed);
	return (ldexp((double)xseed[0], -48) + ldexp((double)xseed[1], -32) +
			ldexp((double)xseed[2], -16));
}

double			ft_rand48(void)
{
	static int				i;
	static unsigned short	rand_seed[3];

	if (++i == 1)
	{
		rand_seed[0] = (unsigned short)(0x330e);
		rand_seed[1] = (unsigned short)(0xabcd);
		rand_seed[2] = (unsigned short)(0x1234);
	}
	return (ft_erand48(rand_seed));
}
