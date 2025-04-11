/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:40:20 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/30 18:42:48 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sizebuff(int n)
{
	int		sizebuff;
	int		mul_10x;

	mul_10x = 10;
	sizebuff = 2;
	if (n == -2147483648)
		return (12);
	else if (n < 0)
	{
		++sizebuff;
		n = -1 * n;
	}
	while (n >= mul_10x && mul_10x < 1000000000)
	{
		++sizebuff;
		mul_10x = mul_10x * 10;
	}
	if (n > 1000000000)
		++sizebuff;
	return (sizebuff);
}

static void	ft_convert(int i, int n, char *digit)
{
	int		div_10x;
	int		first_digit;

	div_10x = 1000000000;
	first_digit = 0;
	while (div_10x > 0)
	{
		if ((n / div_10x) != 0 || first_digit == 1 || div_10x == 1)
		{
			digit[i] = '0' + (n / div_10x);
			first_digit = 1;
			++i;
		}
		n = n - ((n / div_10x) * div_10x);
		div_10x = div_10x / 10;
	}
	digit[i] = '\0';
}

char	*ft_itoa(int n)
{
	int		i;
	int		sizebuff;
	char	*digit;

	i = 0;
	sizebuff = ft_sizebuff(n);
	digit = (char *)ft_calloc(sizebuff, 1);
	if (digit != NULL)
	{
		if (n < 0)
		{
			digit[i] = '-';
			i++;
			if (n == -2147483648)
			{
				digit[i] = '2';
				n = -147483648;
				++i;
			}
			n = -1 * n;
		}
		ft_convert(i, n, digit);
	}
	return (digit);
}
/*
int	main(void)
{
	int n = 2147483647;
	char *digit;
	digit = ft_itoa(n);
	//printf("%d\n", n);
	printf("%s\n", ft_itoa(n));
	free(digit);
}*/
