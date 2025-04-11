/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:20:56 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/28 01:32:45 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	negative(int n, int fd)
{
	write(fd, "-", 1);
	if (n == -2147483648)
	{
		n = -147483648;
		write(fd, "2", 1);
	}
	n = -1 * n;
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		div_10x;
	int		first_digit;
	char	digit;

	div_10x = 1000000000;
	first_digit = 0;
	if (n < 0)
		n = negative(n, fd);
	while (div_10x > 0)
	{
		digit = '0' + (n / div_10x);
		if (digit != '0' || first_digit == 1 || div_10x == 1)
		{
			write(fd, &digit, 1);
			first_digit = 1;
		}
		n = n - ((n / div_10x) * div_10x);
		div_10x = div_10x / 10;
	}
}
