/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:26:58 by ibel-kha          #+#    #+#             */
/*   Updated: 2019/05/22 01:51:06 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int chfr;
	int one;

	if (n < 0)
	{
		n = -n;
		ft_putchar_fd('-', fd);
	}
	if (n == -2147483648)
	{
		ft_putchar_fd(50, fd);
		n = 147483648;
	}
	chfr = 1;
	one = n;
	while ((one /= 10) != 0)
		chfr *= 10;
	while (chfr != 0)
	{
		one = n / chfr;
		n %= chfr;
		chfr /= 10;
		ft_putchar_fd(one + '0', fd);
	}
}
