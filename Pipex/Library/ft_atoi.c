/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:05:58 by karlarod          #+#    #+#             */
/*   Updated: 2025/01/27 23:53:56 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_convert(const char *str, int *num, int neg)
{
	int	i;
	int	aux_num;
	int	n_max;

	i = 0;
	aux_num = 0;
	n_max = 2147483647;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (aux_num > 214489364 && neg == -1 && (str[i] - '0') > 8)
		{
			aux_num = n_max -(aux_num) * 10 + n_max -2 - str[i] - '0';
			neg = 0;
		}
		else if (aux_num > 214489364 && neg != -1 && (str[i] - '0') > 7)
			aux_num = -n_max + (aux_num) * 10 - n_max - 2 + str[i] - '0';
		else
			aux_num = aux_num * 10 + str[i] - '0';
		++i;
	}
	if (neg == -1)
		*num = -1 * aux_num;
	else
		*num = aux_num;
}

static void	ft_space(const char *str, int *num, int neg)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (neg == 0 && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
			++i;
		else if (neg == 0 && str[i] == '+')
		{
			++i;
			neg = 1;
		}
		else if (neg == 0 && str[i] == '-')
		{
			++i;
			neg = -1;
		}
		else if (str[i] >= '0' && str[i] <= '9')
		{
			ft_convert(&str[i], num, neg);
			return ;
		}
		else
			return ;
	}
}

int	ft_atoi(const char *str)
{
	int	*num;
	int	number;
	int	neg;

	number = 0;
	neg = 0;
	num = &number;
	ft_space((char *)str, num, neg);
	return (number);
}
